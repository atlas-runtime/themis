/**
 * A Dynamic Programming based solution for calculating Longest Increasing Subsequence
 * https://en.wikipedia.org/wiki/Longest_increasing_subsequence
 */

function lis (arr) {

  const length = arr.length
  const dp = Array(length).fill(1)

  let res = 1

  for (let i = 0; i < length; i++) {
    for (let j = 0; j < i; j++) {
      if (arr[i] > arr[j]) {
        dp[i] = Math.max(dp[i], 1 + dp[j])
        if (dp[i] > res) {
          res = dp[i]
        }
      }
    }
  }

  //console.log('Length of Longest Increasing Subsequence is:', res)
}

export function LongestIncreasingSubsequence_bench(size){
  let arr = new Array(size);
  for(let i= 0; i<size; i++){
    arr[i] = i;
  }
  lis(arr);
  return "bench_done"

}
// LongestIncreasingSubsequence_bench(10000)