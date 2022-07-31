/*
 * Gnome sort is a sort algorithm that moving an element to its proper place is accomplished by a series of swap
 * more information: https://en.wikipedia.org/wiki/Gnome_sort
 *
 */
function gnomeSort (items) {
  if (items.length <= 1) {
    return
  }

  let i = 1

  while (i < items.length) {
    if (items[i - 1] <= items[i]) {
      i++
    } else {
      [items[i], items[i - 1]] = [items[i - 1], items[i]]

      i = Math.max(1, i - 1)
    }
  }
}

// Implementation of gnomeSort

export function GnomeSort_bench(size){
  var arr = new Array(size);

  for (let i=0; i<size; i++){
    arr[i]=size-i;
  }
  gnomeSort(arr)
  return "Gbench_done"
}
// GnomeSort_bench(5000)
