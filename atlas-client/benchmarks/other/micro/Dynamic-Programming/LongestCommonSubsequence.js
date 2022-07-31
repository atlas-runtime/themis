/*
    * Given two sequences, find the length of longest subsequence present in both of them.
    * A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous.
    * For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”
*/

function longestCommonSubsequence (x, y, str1, str2, dp) {
  if (x === -1 || y === -1) {
    return 0
  } else {
    if (dp[x][y] !== 0) {
      return dp[x][y]
    } else {
      if (str1[x] === str2[y]) {
        dp[x][y] = 1 + longestCommonSubsequence(x - 1, y - 1, str1, str2, dp)
        return dp[x][y]
      } else {
        dp[x][y] = Math.max(longestCommonSubsequence(x - 1, y, str1, str2, dp), longestCommonSubsequence(x, y - 1, str1, str2, dp))
        return dp[x][y]
      }
    }
  }
}

function repeat(pattern, count) {
    if (count < 1) return '';
    var result = '';
    while (count > 1) {
        if (count & 1) result += pattern;
        count >>= 1, pattern += pattern;
    }
    return result + pattern;
}

export function LongestCommonSubsequence_bench (size) {
  let str1 = repeat('a',size);
  let str2 = repeat('b',size);
  const dp = new Array(str1.length + 1).fill(0).map(x => new Array(str2.length + 1).fill(0))
  const res = longestCommonSubsequence(str1.length - 1, str2.length - 1, str1, str2, dp)
  return "bench_done"
}
// LongestCommonSubsequence_bench(13)
