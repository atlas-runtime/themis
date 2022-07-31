/*
 * Wiggle sort sorts the array into a wave like array.
 * An array ‘arr[0..n-1]’ is sorted in wave form if arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= …..
 *
 */

/* eslint no-extend-native: ["off", { "exceptions": ["Object"] }] */
Array.prototype.wiggleSort = function () {
  for (let i = 0; i < this.length; ++i) {
    const shouldNotBeLessThan = i % 2
    const isLessThan = this[i] < this[i + 1]
    if (shouldNotBeLessThan && isLessThan) {
      [this[i], this[i + 1]] = [this[i + 1], this[i]]
    }
  }
  return this
}

// Implementation of wiggle sort

export function WiggleSort_bench(size){
	var arr = new Array(size);
	for (let i=0; i<size; i++){
		arr[i]=i;
	}
	arr.wiggleSort()
  return "bench_done"
// Array after wiggle sort

}
// WiggleSort_bench(1000000)