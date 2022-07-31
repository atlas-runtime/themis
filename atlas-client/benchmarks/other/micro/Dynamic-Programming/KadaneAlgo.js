function KadaneAlgo (array) {
  let cummulativeSum = 0
  let maxSum = 0
  for (var i = 0; i < array.length; i++) {
    cummulativeSum = cummulativeSum + array[i]
    if (cummulativeSum < 0) {
      cummulativeSum = 0
    } else if (maxSum < cummulativeSum) {
      maxSum = cummulativeSum
    }
  }
  return maxSum
  // This function returns largest sum contigous sum in a array
}
export function KadaneAlgo_bench (size) {

  var myArray = new Array(size);
  for(let i=0; i < size; i++){
    myArray[i] = size-i;
  }
  var result = KadaneAlgo(myArray)
  return "bench_done"
}
// KadaneAlgo_bench(1000000)