function maximumNonAdjacentSum (nums) {
  /*
         * Find the maximum non-adjacent sum of the integers in the nums input list
         * :param nums: Array of Numbers
         * :return: The maximum non-adjacent sum
    */

  if (nums.length < 0) return 0

  let maxIncluding = nums[0]
  let maxExcluding = 0

  for (const num of nums.slice(1)) {
    const temp = maxIncluding
    maxIncluding = maxExcluding + num
    maxExcluding = Math.max(temp, maxExcluding)
  }

  return Math.max(maxExcluding, maxIncluding)
}


export function MaxNonAdjacentSum_bench(size) {

  let arr = new Array (size);

  for (let i = 0; i < size; i++) {
    arr[i] = i;
  }
  maximumNonAdjacentSum(arr)
  return "bench_done"
}

// MaxNonAdjacentSum_bench(1000000)