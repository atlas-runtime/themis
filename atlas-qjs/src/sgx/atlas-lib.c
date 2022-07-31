const char *srl_code = "import * as std from 'std';import * as os from 'os';globalThis.std = std;globalThis.os = os;globalThis.current_nonce = 0;globalThis.atlas_data = 0;const base=['string','boolean','symbol','number','object','nan','infinity','null','function','array','regexp'];const subtyping={'string':{},'boolean':{},'symbol':{},'function':{},'number':{'nan':{},'infinity':{'-inf':{},'+inf':{}}},'null':{},'object':{'function':{},'date':{},'array':{},'regexp':{}}};const core_isSpecialPrimitive=function isSpecialPrimitive(value){return(value===null)||(value===undefined)||(value!==value)};const core_getSpecialPrimitive=function getSpecialPrimitive(value){if(value===null){return 'null'}else if(value===undefined){return 'undefined'}else if(value!==value){return 'NaN'}};const core_getType=function getType(value){if(core_getSpecialPrimitive(value)){return core_getSpecialPrimitive(value)}switch(typeof value){case 'object':switch(utils_typeOf(value)){case '':return 'null';default:return(utils_typeOf(value))}default:return(typeof value);case 'function':return 'function'}};const core_transform=function transform(code,options){if(!options){return code}options.getType=options.getType||core_getType;let tsf=options.transform[options.getType(code)]||options.transform['_'];return options.combine(tsf(code,options))};let print=(...args)=>console.log(...args);let native_map=new Map();let reverse_map=new Map();function build_native_maps(){var _getPropertyNames=function(obj,iterateSelfBool,iteratePrototypeBool){let props=[];do{if(iterateSelfBool){Object.getOwnPropertyNames(obj).forEach(function(prop){if(props.indexOf(prop)===-1){props.push(prop)}})}if(!iteratePrototypeBool){break}iterateSelfBool=true}while(obj=Object.getPrototypeOf(obj));return props};var getOwnAndPrototypeEnumerablesAndNonenumerables=function(obj){return _getPropertyNames(obj,true,true)};var es=[\"Array\",\"ArrayBuffer\",\"Boolean\",\"DataView\",\"Date\",\"decodeURI\",\"decodeURIComponent\",\"encodeURI\",\"encodeURIComponent\",\"Error\",\"escape\",\"eval\",\"EvalError\",\"Float32Array\",\"Float64Array\",\"Function\",\"hasOwnProperty\",\"Infinity\",\"Int16Array\",\"Int32Array\",\"Int8Array\",\"isFinite\",\"isNaN\",\"isPrototypeOf\",\"JSON\",\"Map\",\"Math\",\"NaN\",\"Number\",\"Object\",\"parseFloat\",\"parseInt\",\"Promise\",\"propertyIsEnumerable\",\"Proxy\",\"RangeError\",\"ReferenceError\",\"RegExp\",\"Reflect\",\"Set\",\"String\",\"Symbol\",\"SyntaxError\",\"toLocaleString\",\"toString\",\"TypeError\",\"Uint16Array\",\"Uint32Array\",\"Uint8Array\",\"Uint8ClampedArray\",\"unescape\",\"URIError\",\"valueOf\",\"WeakMap\",\"WeakSet\"];let eval_whole;let whole;for(let i=0;i<es.length;i+=1){let obj=eval(es[i]);native_map.set(es[i],obj);reverse_map.set(obj,es[i]);let properties=getOwnAndPrototypeEnumerablesAndNonenumerables(obj);for(let j=0;j<properties.length;j+=1){try{whole=es[i]+\".\"+properties[j];eval_whole=eval(whole);if(eval_whole==undefined){eval_whole='undefined'}if(eval_whole==null){eval_whole='null'}if(!native_map.has(whole)){native_map.set(whole,eval_whole)}if(!reverse_map.has(eval_whole)){reverse_map.set(eval_whole,whole)}}catch(e){}}}}build_native_maps();const srl_tryNativeObj=function tryNativeObj(obj){let s='';switch(obj){case(Object):s='Object';break;case(Object.keys):s=JSON.stringify('Object.keys');break;case(Object.prototype):s=JSON.stringify('Object.prototype');break;case(Array):s=JSON.stringify('Array');break;default:return{isNative:false}}return{isNative:true,serialized:s}};function isNative(value){var toString=Object.prototype.toString;var fnToString=Function.prototype.toString;var reHostCtor=/^\\[object .+?Constructor\\]$/;var reNative=RegExp('^'+String(toString).replace(/[.*+?^${}()|[\\]\\/\\\\]/g,'\\\\$&').replace(/toString|(function).*?(?=\\\\\\()| for .+?(?=\\\\\\])/g,'$1.*?')+'$');var type=typeof value;return type=='function'?reNative.test(fnToString.call(value)):(value&&type=='object'&&reHostCtor.test(toString.call(value)))||false}const baseTransform={};baseTransform['_']=(v)=>{if(typeof(v)==='object'){return[JSON.stringify(Array.from(v.entries()))]}else{return[v.toString()]}};baseTransform['function']=(v)=>{if(isNative(v)){return[JSON.stringify(reverse_map.get(v))]}return[JSON.stringify(v.toString())]};baseTransform['error']=(v)=>{return['new ',v.name,'(\"',v.message,'\")']};baseTransform['date']=(v)=>{return['new Date(\"',v.toString(),'\")']};baseTransform['undefined']=()=>{return[JSON.stringify('undefined')]};baseTransform['null']=()=>{return[JSON.stringify('null')]};baseTransform['string']=(v)=>{return[JSON.stringify(v)];};baseTransform['object']=(v)=>{if(isNative(v)){let a=JSON.stringify(reverse_map.get(v));return[]}let r=['{'];for(let key in v){if(!utils_owns(v,key)){continue}r=r.concat([JSON.stringify(key),': ',srl_stringify(v[key]),', '])}return(r.length>2)?r.slice(0,r.length-1).concat(['}']):['{}']};baseTransform['array']=(v)=>{let r=['['];for(let i=0;i<v.length;i+=1){if(v[i]===undefined){r.push(stringify('undefined'))}else if(v[i]===null){r.push(stringify('null'))}else{if(isNative(v[i])){let a=reverse_map.get(v[i]);r.push(stringify(a))}else{r.push(stringify(v[i]))}}if(i!==v.length-1){r.push(', ')}}return r.concat([']'])};const srl_baseCombine=(args)=>args.join('');const srl_stringify=function stringify(code){if(utils_isCyclic(code)){return false}return core_transform(code,{transform:baseTransform,combine:srl_baseCombine})};let defaultOptions={name:'',depth:0,expandBoxedPrimitives:false,traverseHierarchy:false,overwritePrompt:false,colors:false,combine:(args)=>args.join('')};defaultOptions.palette=['str','symbol','fun','num','null','undefined','boxed','regexp','key'].reduce(function(o,i){o[i]=function(s){return s};return o},{});if(typeof String.prototype.parseFunction!='function'){String.prototype.parseFunction2=function(){var fname=this.match(/function(.*?)\\(/)[1].trim().toString();let nthis=this.replace(fname,\"\");let funcReg=/function *\\(([^()]*)\\)[ \\n\\t]*{(.*)}/gmi;let match=funcReg.exec(nthis.replace(/\\n/g,' '));if(match){let args=match[1].split(',');let body=match[2];const f=new Function(args,body);Object.defineProperty(f,\"name\",{value:fname});return f}return null};String.prototype.parseFunction=function(){return eval('('+this+')')}}function fix_parse(obj){if(typeof(obj)==='string'&&(native_map.get(obj)!==null||native_map.get(obj)!==undefined)){return native_map.get(obj)}else if(typeof(obj)==='string'&&(obj.startsWith('function')||obj.includes('function'))){return obj.parseFunction()}if(typeof(obj)==='object'&&(Object.entries(obj)===null||Object.entries(obj)==undefined)){return obj}for(const[key,value]of Object.entries(obj)){if(typeof value==='string'){if(value.startsWith('function')||value.includes('function')){let ff=value.parseFunction();obj[key]=ff}else if(value==='undefined'){obj[key]=undefined}else if(value==='null'){obj[key]=null}else if(reverse_map.has(value)){let a=reverse_map.get(value);obj[key]=reverse_map.get(value)}}else if(typeof value==='object'){obj[key]=fix_parse(value)}}return obj}export function parse(code,options){let obj;if(typeof code!=='string'){return code}options=utils_merge(defaultOptions,options);if(code==='undefined'){return undefined}if(code==='null'){return null}obj=fix_parse(JSON.parse(code));return obj};export function stringify(code,options){options=utils_merge(defaultOptions,options);let s=srl_stringify(code,options);return s};const utils_isNative=function isNative(value){let toString=Object.prototype.toString;let fnToString=Function.prototype.toString;let hostCtr=/^\\[object .+?Constructor\\]$/;let reNative=RegExp('^'+String(toString).replace(/[.*+?^${}()|[\\]\\/\\\\]/g,'\\\\$&').replace(/toString|(function).*?(?=\\\\\\()| for .+?(?=\\\\\\])/g,'$1.*?')+'$');let type=typeof value;if(type==='function'){return reNative.test(fnToString.call(value))}else{return(value&&type==='object'&&hostCtr.test(toString.call(value)))}};const utils_typeOf=function typeOf(v){return({}).toString.call(v).match(/\\s([a-zA-Z]+)/)[1].toLowerCase()};const utils_owns=function owns(obj,prop){return Object.prototype.hasOwnProperty.call(obj,prop)};let utils_generateID=function(){return Math.random().toString(36).substring(7)};let utils_isCyclic=function(obj){try{JSON.stringify(obj);return false}catch(e){return true}};const utils_merge=function(o1,o2,options){options=options||{};if(utils_typeOf(o1)!==utils_typeOf(o2)){if(options.onTypeMismatch){return options.onTypeMismatch(o1,o2)}return o1}if(isCyclic(o1)||isCyclic(o2)){if(options.onCycle){return options.onCycle(o1,o2)}return o1}if(options.clone){o1=clone(o1);o2=clone(o2)}if(utils_typeOf(o1)!=='object'){if(options.onType&&options.onType[utils_typeOf(o1)]){return options.onType[utils_typeOf(o1)](o1,o2)}return o2}let result=options.clone?clone(o1):o1;if(options.onType&&options.onType['object']){return options.onType['object'](o1,o2,options,result)}options.clone=false;for(let k in o2){result[k]=result[k]?merge(result[k],o2[k],options):o2[k]}return result};globalThis.parse=parse;globalThis.stringify=stringify;";