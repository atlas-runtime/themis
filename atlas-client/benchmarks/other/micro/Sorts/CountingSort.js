/*
 * Counting sort is an algorithm for sorting a collection of objects according to keys that are small integers;
 * that is, it is an integer sorting algorithm.
 * more information: https://en.wikipedia.org/wiki/Counting_sort
 * counting sort visualization: https://www.cs.usfca.edu/~galles/visualization/CountingSort.html
 */

function countingSort (arr, min, max) {
  let i
  let z = 0
  const count = []

  for (i = min; i <= max; i++) {
    count[i] = 0
  }

  for (i = 0; i < arr.length; i++) {
    count[arr[i]]++
  }

  for (i = min; i <= max; i++) {
    while (count[i]-- > 0) {
      arr[z++] = i
    }
  }

  return arr
}


export function CountingSort_bench(size){
  var arr = new Array(size);

  for (let i=0; i<size; i++){
    arr[i]=size-i;
  }
  countingSort(arr,0,size)
  return "bench_done"
}
// CountingSort_bench(1000000)