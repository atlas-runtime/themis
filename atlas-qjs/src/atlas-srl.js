/*
 * The core walks a JavaScript DAG, and applies provided transformations
 */

//core.js
const base = [
  // core
  'string',
  'boolean',
  'symbol',
  'number',
  'object',
  // special primitives
  'nan',
  'infinity',
  'null',
  // special objects
  'function',
  'array',
  'regexp',
];

const subtyping = {
  'string': {},
  'boolean': {},
  'symbol': {},
  'function': {},
  'number': {
    'nan': {},
    'infinity': {
      '-inf': {},
      '+inf': {},
    },
  },
  'null': {},
  'object': {
    'function': {},
    'date': {},
    'array': {},
    'regexp': {},
  },
};

const core_isSpecialPrimitive = function isSpecialPrimitive(value) {
  return (value === null) || (value === undefined) || (value !== value);
};

const core_getSpecialPrimitive = function getSpecialPrimitive(value) {
  if (value === null) {
    return 'null';
  } else if (value === undefined) {
    return 'undefined';
  } else if (value !== value) {
    return 'NaN';
  }
};

const core_getType = function getType(value) {
  if (core_getSpecialPrimitive(value)) {
    // undefined, null,
    return core_getSpecialPrimitive(value);
  }

  switch (typeof value) {
    case 'object':
      switch (utils_typeOf(value)) {
        case '':
          // FIXME
          return 'null';
        default:
          // object, null, array, etc
          return (utils_typeOf(value));
      }
    default:
      return (typeof value);
    case 'function':
      return 'function';
  }
};

// options provides a mapping from value types to results.
const core_transform = function transform(code, options) {
  if (!options) {
    return code;
  }
  options.getType = options.getType || core_getType;
  let tsf = options.transform[options.getType(code)] || options.transform['_'];
  return options.combine(tsf(code, options));
  
};

//serialization.js
let print = (...args) => console.log(...args);

let native_map = new Map();
let reverse_map = new Map();

function build_native_maps(){

  var _getPropertyNames = function (obj,iterateSelfBool, iteratePrototypeBool) {

    let props = [];

    do {
      if (iterateSelfBool) {
        Object.getOwnPropertyNames(obj).forEach(function(prop) {
          if (props.indexOf(prop) === -1 ) {
            props.push(prop);
          }
        });
      }
      if (!iteratePrototypeBool) {
        break;
      }
      iterateSelfBool = true;
    } while (obj = Object.getPrototypeOf(obj));

    return props;
  }

  var getOwnAndPrototypeEnumerablesAndNonenumerables = function (obj) {
    return _getPropertyNames(obj, true, true);
  }

  var es = [
    "Array",
    "ArrayBuffer",
    // "Atomics",
    // "BigInt",
    // "BigInt64Array",
    // "BigUint64Array",
    "Boolean",
    // "constructor",
    "DataView",
    "Date",
    "decodeURI",
    "decodeURIComponent",
    "encodeURI",
    "encodeURIComponent",
    "Error",
    "escape",
    "eval",
    "EvalError",
    "Float32Array",
    "Float64Array",
    "Function",
    "hasOwnProperty",
    "Infinity",
    "Int16Array",
    "Int32Array",
    "Int8Array",
    "isFinite",
    "isNaN",
    "isPrototypeOf",
    "JSON",
    "Map",
    "Math",
    "NaN",
    "Number",
    "Object",
    "parseFloat",
    "parseInt",
    "Promise",
    "propertyIsEnumerable",
    "Proxy",
    "RangeError",
    "ReferenceError",
    "RegExp",
    "Reflect",
    "Set",
    // "SharedArrayBuffer",
    "String",
    "Symbol",
    "SyntaxError",
    "toLocaleString",
    "toString",
    "TypeError",
    "Uint16Array",
    "Uint32Array",
    "Uint8Array",
    "Uint8ClampedArray",
    "unescape",
    "URIError",
    "valueOf",
    "WeakMap",
    "WeakSet"
  ]

  // es = ['Object','Reflect'];

  let eval_whole;
  let whole;
  for(let i=0;i<es.length; i++){

    let obj = eval(es[i])
    // print(es[i],obj)
    
    native_map.set(es[i],obj)
    reverse_map.set(obj,es[i])

    let properties = getOwnAndPrototypeEnumerablesAndNonenumerables(obj);

    for(let j=0;j<properties.length;j++){

      try{
        whole = es[i] + "." + properties[j]
        eval_whole = eval(whole);
         // print(whole,eval_whole)
        if(eval_whole == undefined) eval_whole = 'undefined';
        if(eval_whole == null) eval_whole = 'null';

        if(!native_map.has(whole))
          native_map.set(whole, eval_whole)
      
        if(!reverse_map.has(eval_whole))
          reverse_map.set(eval_whole, whole)

      }catch(e){
        // TypeError: 'caller', 'callee', and 'arguments' properties
        // may not be accessed on strict mode functions or the arguments objects for calls to them
        // print(e)
      }
    }
  }

  // //prints
  // for (var [key, value] of native_map) {
  //   console.log(key);
  //   if(typeof value === 'object')continue;
  //   if(typeof value === 'symbol'){
  //     console.log(value.toString())
  //     continue;
  //   }
  //   console.log(value)
  //   console.log("*******************")
  // }
  // for (var [key, value] of reverse_map) {
  //   if(typeof key === 'object')continue;
  //   if(typeof key === 'symbol'){
  //     console.log(key.toString())
  //     continue;
  //   }
  //   console.log(key)
  //   console.log(value)
  //   console.log("*******************")
  // }
}

build_native_maps();

// 
const srl_tryNativeObj = function tryNativeObj(obj) {
  // FIXME: this requires a weak map
  let s = '';

  //  for (const [key, value] of Object.entries(obj)) {
  //   print(key,value)
  // }
  switch (obj) {
    case (Object):
      s = 'Object';
      break;
    case (Object.keys):
      s = JSON.stringify('Object.keys');
      break;
    case (Object.prototype):
      s = JSON.stringify('Object.prototype');
      break;
    case (Array):
      s = JSON.stringify('Array');
      break;
    default:
      return {isNative: false};
  }
  return {isNative: true, serialized: s};
};


//https://davidwalsh.name/detect-native-function
function isNative(value) {
  // print(JSON.stringify(value))
  var toString = Object.prototype.toString;
  
  // Used to resolve the decompiled source of functions
  var fnToString = Function.prototype.toString;
  
  // Used to detect host constructors (Safari > 4; really typed array specific)
  var reHostCtor = /^\[object .+?Constructor\]$/;

  // Compile a regexp using a common native method as a template.
  // We chose `Object#toString` because there's a good chance it is not being mucked with.
  var reNative = RegExp('^' +
    // Coerce `Object#toString` to a string
    String(toString)
    // Escape any special regexp characters
    .replace(/[.*+?^${}()|[\]\/\\]/g, '\\$&')
    // Replace mentions of `toString` with `.*?` to keep the template generic.
    // Replace thing like `for ...` to support environments like Rhino which add extra info
    // such as method arity.
    .replace(/toString|(function).*?(?=\\\()| for .+?(?=\\\])/g, '$1.*?') + '$'
  );

  var type = typeof value;
    return type == 'function'
      // Use `Function#toString` to bypass the value's own `toString` method
      // and avoid being faked out.
      ? reNative.test(fnToString.call(value))
      // Fallback to a host object check because some environments will represent
      // things like typed arrays as DOM methods which may not conform to the
      // normal native pattern.
      : (value && type == 'object' && reHostCtor.test(toString.call(value))) || false;
}




const baseTransform = {};
baseTransform['_'] = (v) => {
  // dkarnikis fix
  if( typeof(v) === 'object'){
    /* convert map to array and then serialize */
    return [ JSON.stringify(Array.from(v.entries())) ]
  }else{
    return [ v.toString() ];
  }
};

baseTransform['function'] = (v) => {

  if (isNative(v) ) { //reverse_map.has(v[i]
    return [ JSON.stringify(reverse_map.get(v)) ];
  }
  //edw evala JSON,stringify pou epistrefei synarthsh
  // print
  return [JSON.stringify(v.toString())] ;
};

baseTransform['error'] = (v) => {
  // console.log("error")
  // FIXME: local or remote stack trace?
  return ['new ', v.name, '("', v.message, '")'];
};
baseTransform['date'] = (v) => {
  // console.log("date")
  // Dates require quotes
  return ['new Date("', v.toString(), '")'];
};

baseTransform['undefined'] = () => {
  // console.log("undef")
  return [JSON.stringify('undefined')];
};
baseTransform['null'] = () => {
  return [JSON.stringify('null')];
};
baseTransform['string'] = (v) => {
  // console.log("str")
  return [JSON.stringify(v)]; // ['"', v, '"'];
};

  // TODO: add v to the baseTransform to each of the types

baseTransform['object'] = (v) => {

  // FIXME: (i) built-ins, (ii) objects that have a constructor
 if (isNative(v) ) {//|| reverse_map.has(v)
    let a = JSON.stringify(reverse_map.get(v));

    return [];
  }
  let r = ['{'];
  for (let key in v) {
    if (!utils_owns(v, key)) {
      continue;
    }
    r = r.concat([JSON.stringify(key), ': ', srl_stringify(v[key]), ', ']);
  }
  return (r.length > 2)? r.slice(0, r.length - 1).concat(['}']) : ['{}'];
};

//TODO: Implement cycle detection
// Create map of object to their sha256 hash value
// Use this as a "set" to check if an object has been seen before

baseTransform['array'] = (v) => {
  // print(v)
  
  // console.log("arr")
  let r = ['['];
  // let cm = (v.length > 3) ? ',\n' : ', ';
  for (let i = 0; i < v.length; i++) {
    // console.log("v[i]: ", v[i])

    if (v[i] === undefined ){
      r.push(stringify('undefined'));
    }else if(v[i] === null ){
      r.push(stringify('null'));

    }else{

      if(isNative(v[i])){

        let a = reverse_map.get(v[i])
        // print(a,typeof a)
    
        r.push(stringify(a));
      }else{

        // if(reverse_map.has(v[i])){
        //   print(reverse_map.get(v[i]))
        // }

        r.push(stringify(v[i]));
      }
        
    }

    if (i !== v.length - 1) {
      r.push(', ');
    }
  }
  return r.concat([']']);
};



const srl_baseCombine = (args) => args.join('');

const srl_stringify = function stringify(code) {

  if (utils_isCyclic(code)) {
    return false;
  }
  return core_transform(code, {transform: baseTransform, combine: srl_baseCombine} );
};

let defaultOptions = {
  name: '',
  depth: 0,
  expandBoxedPrimitives: false,
  traverseHierarchy: false,
  overwritePrompt: false,
  colors: false,
  combine: (args) => args.join(''),
};

defaultOptions.palette = [
  'str',
  'symbol',
  'fun',
  'num',
  'null',
  'undefined',
  'boxed',
  'regexp',
  'key',
].reduce(function(o, i) {
  // each type gets a function that simply returns the contents
  o[i] = function(s) {
    return s;
  };
  return o;
}, {});

if (typeof String.prototype.parseFunction != 'function') {
    
    String.prototype.parseFunction2 = function () {
        // extract the function name
        var fname = this.match(/function(.*?)\(/)[1].trim().toString();
        // trim the function name
        let nthis = this.replace(fname, "");
        // parse tha arguments and the body without the name
        let funcReg = /function *\(([^()]*)\)[ \n\t]*{(.*)}/gmi;
        let match = funcReg.exec(nthis.replace(/\n/g, ' '));
        // print(fname)
        // print(match)
        if(match) {

          let args = match[1].split(',')
          let body = match[2]
          //kainourgio anonymous omws function

          const f = new Function(args, body);
          
          //grafw to f.name me to onoma ths synarthshs
          Object.defineProperty(f, "name", { value: fname });
          return f;
        }
        // console.log("XD")
        return null;
    };

    String.prototype.parseFunction = function () {
       return eval('('+this+')');
    };
}



function fix_parse(obj){
 
  if ( typeof(obj) === 'string' && (native_map.get(obj) !== null || native_map.get(obj) !== undefined)){
    return native_map.get(obj);

  }else if( typeof(obj) === 'string' && ( obj.startsWith('function') || obj.includes('function'))) {
    return obj.parseFunction();
  }

  if(typeof(obj) === 'object' && (Object.entries(obj) === null || Object.entries(obj) == undefined)) {
     return obj;
  }

  for (const [key, value] of Object.entries(obj)) {
    // print("key: ",key," value: ",value.toString())
    if(typeof value === 'string'){

        if(value.startsWith('function') || value.includes('function')){

          let ff = value.parseFunction();
          obj[key] = ff

        }else if (value === 'undefined'){
          obj[key] = undefined;

        }else if (value === 'null'){ 
          obj[key] = null;

        }else if(reverse_map.has(value)){
          // print("value",value,typeof value)
          let a = reverse_map.get(value);
          // print("a",a,typeof a)
          obj[key] = reverse_map.get(value);
        }

    }else if(typeof value === 'object'){
      obj[key] = fix_parse(value)
    }

  }
  return obj;
}




function parse(code, options) {

  let obj;
  // in any other case return the value
  if (typeof code !== 'string') {
    return code;
  }

  options = utils_merge(defaultOptions, options);
  // print(code)
  if(code === 'undefined') return undefined;

  if(code === 'null') return null;
  obj = fix_parse(JSON.parse(code));

  return obj;
};


function stringify (code, options) {

  options = utils_merge(defaultOptions, options);

  let s = srl_stringify(code, options);

  return s;
};


//utils_js
const utils_isNative = function isNative(value) {
  // Used to resolve the internal `[[Class]]` of values
  let toString = Object.prototype.toString;

  // Used to resolve the decompiled source of functions
  let fnToString = Function.prototype.toString;

  // Used to detect host constructors (Safari > 4; really typed array specific)
  let hostCtr = /^\[object .+?Constructor\]$/;

  // Compile a regexp using a common native method as a template.
  // Chose `Object#toString` because there's a good chance it is not
  // being mucked with.
  let reNative = RegExp('^' +
      // Coerce `Object#toString` to a string
      String(toString)
      // Escape any special regexp characters
          .replace(/[.*+?^${}()|[\]\/\\]/g, '\\$&')
          // Replace mentions of `toString` with `.*?` to keep the template
          // generic. Replace thing like `for ...` to support environments
          // like Rhino which add extra info such as method arity.
          .replace(/toString|(function).*?(?=\\\()| for .+?(?=\\\])/g, '$1.*?')
      + '$'
  );
  let type = typeof value;
  if (type === 'function') {
    // Use `Function#toString` to bypass the value's own `toString` method
    // and avoid being faked out.
    return reNative.test(fnToString.call(value));
  } else {
    // Fallback to a host object check because some environments will represent
    // things like typed arrays as DOM methods which may not conform to the
    // normal native pattern.
    return (value && type === 'object' && hostCtr.test(toString.call(value)));
  }
};

const utils_typeOf = function typeOf(v) {
  return ({}).toString.call(v).match(/\s([a-zA-Z]+)/)[1].toLowerCase();
};

// If obj.hasOwnProperty has been overridden, then calling
// obj.hasOwnProperty(prop) will break.
// See: https://github.com/joyent/node/issues/1707
const utils_owns = function owns(obj, prop) {
  return Object.prototype.hasOwnProperty.call(obj, prop);
};

// This is not crypto-secure
let utils_generateID = function() {
  return Math.random().toString(36).substring(7);
};

let utils_isCyclic = function(obj) {
  try {
    JSON.stringify(obj);
    return false;
  } catch (e) {
    return true;
  }
};

// on type mismatch, use approriate resolution or, by default, return o1 -- so
// that defaults are never overwritten!
// but if type is the same (and not object -- i.e., no recursion) pick o2!
// options:
// * onTypeMismatch: what do do if the two objects are not of the same type
// * onType[x] = function (o1, o2): what to do on type mismatches
// * onCycle: what to do if any of the object has a cycle
// * clone: [false] clone object before anything
const utils_merge = function(o1, o2, options) {
  options = options || {};

  // merge(1, [1,2,3]) -> [1,2,3]
  if (utils_typeOf(o1) !== utils_typeOf(o2)) {
    if (options.onTypeMismatch) {
      return options.onTypeMismatch(o1, o2);
    }
    return o1;
  }

  if (isCyclic(o1) || isCyclic(o2)) {
    if (options.onCycle) {
      return options.onCycle(o1, o2);
    }
    return o1;
  }

  if (options.clone) {
    o1 = clone(o1);
    o2 = clone(o2);
  }

  // merge(1, 2) -> 2
  if (utils_typeOf(o1) !== 'object') {
    // at this point o1 and o2 have the same type
    if (options.onType && options.onType[utils_typeOf(o1)]) {
      return options.onType[utils_typeOf(o1)](o1, o2);
    }
    return o2;
  }

  let result = options.clone? clone(o1) : o1;

  if (options.onType && options.onType['object']) {
    // user can decide whether to use pre-populated 'result'
    return options.onType['object'](o1, o2, options, result);
  }

  options.clone = false;
  // eslint-disable-next-line guard-for-in
  for (let k in o2) {
    // we won't keep cloning recursively!
    result[k] = result[k]? merge(result[k], o2[k], options) : o2[k];
  }
  return result;
};
atlas.stringify = stringify;
atlas.parse = parse;
