/*
 * Shell Sort sorts an array based on  insertion sort algorithm
 * more information: https://en.wikipedia.org/wiki/Shellsort
 *
 */
function shellSort (items) {
  var interval = 1

  while (interval < items.length / 3) {
    interval = interval * 3 + 1
  }

  while (interval > 0) {
    for (var outer = interval; outer < items.length; outer++) {
      var value = items[outer]
      var inner = outer

      while (inner > interval - 1 && items[inner - interval] >= value) {
        items[inner] = items[inner - interval]
        inner = inner - interval
      }
      items[inner] = value
    }
    interval = (interval - 1) / 3
  }
  return items
}

// Implementation of shellSort
export function ShellSort_bench(size){
  var arr = new Array(size);

  for (let i=0; i<size; i++){
    arr[i]=size-i;
  }
  shellSort(arr)
  return "bench_done"
}
// ShellSort_bench(1000000)