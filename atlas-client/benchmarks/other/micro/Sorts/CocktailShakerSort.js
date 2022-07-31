/*
 * Cocktail shaker sort is a sort algorithm that is a bidirectional bubble sort
 * more information: https://en.wikipedia.org/wiki/Cocktail_shaker_sort
 * more information: https://en.wikipedia.org/wiki/Bubble_sort
 *
 */
function cocktailShakerSort (items) {
  for (let i = items.length - 1; i > 0; i--) {
    let swapped = false
    let j

    // backwards
    for (j = items.length - 1; j > i; j--) {
      if (items[j] < items[j - 1]) {
        [items[j], items[j - 1]] = [items[j - 1], items[j]]
        swapped = true
      }
    }

    // forwards
    for (j = 0; j < i; j++) {
      if (items[j] > items[j + 1]) {
        [items[j], items[j + 1]] = [items[j + 1], items[j]]
        swapped = true
      }
    }
    if (!swapped) {
      return items
    }
  }
  return items
}

// Implementation of cocktailShakerSort



export function CocktailShakerSort_bench(size){
  var arr = new Array(size);
  
  for (let i=0; i<size; i++){
    arr[i]=size-i;
  }
  cocktailShakerSort(arr)
  return "bench_done"

}
// CocktailShakerSort_bench(5000)