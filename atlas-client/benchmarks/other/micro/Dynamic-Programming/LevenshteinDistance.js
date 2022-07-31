/**
 * A Dynamic Programming based solution for calculation of the Levenshtein Distance
 * https://en.wikipedia.org/wiki/Levenshtein_distance
 */

function minimum (a, b, c) {
  if (a < b && a < c) {
    return a
  } else if (b < a && b < c) {
    return b
  } else {
    return c
  }
}

function costOfSubstitution (x, y) {
  return x === y ? 0 : 1
}

function calculate (x, y) {
  const dp = new Array(x.length + 1)
  for (let i = 0; i < x.length + 1; i++) {
    dp[i] = new Array(y.length + 1)
  }

  for (let i = 0; i < x.length + 1; i++) {
    for (let j = 0; j < y.length + 1; j++) {
      if (i === 0) {
        dp[i][j] = j
      } else if (j === 0) {
        dp[i][j] = i
      } else {
        dp[i][j] = minimum(dp[i - 1][j - 1] + costOfSubstitution(x.charAt(i - 1), y.charAt(j - 1)), dp[i - 1][j] + 1, dp[i][j - 1] + 1)
      }
    }
  }

  return dp[x.length][y.length]
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

export function LevenshteinDistance_bench(size) {
  const a = repeat('a',size) // enter your string here
  const b = repeat('b',size) // enter your string here

  // console.log('Levenshtein distance between ' + a + ' and ' + b + ' is: ')
  calculate(a, b)
  return "bench_done"
}
// LevenshteinDistance_bench(2000)