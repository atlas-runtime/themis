export function MemRead_bench(size){

  function newArray(size){
    let t = new Array(size);
    for (let i=0; i<t.length; i++){
        t[i] = i;
    }
    return t;
  }

  function getRandomInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min) + min); //The maximum is exclusive and the minimum is inclusive
  }

  let t = newArray(size);
  let a = 0;
  let b = 0;
  // generate random number
  for (let i=0; i<1000000; i++){
    a = getRandomInt(0, size);
    b = t[a]
  }
}