/**
 * @param {number} n
 * @return {number}
 */
const distinctSequences = function (n) {
  if (n === 1) return 6
  // dp[i][j][k] 长为 i, 最后两个元素是 j, k
  // dp[1][.][.] = 1
  const dp = Array(n).fill(0).map(() => Array(7).fill(0).map(() => Array(7).fill(0)))
  const gcd = (a, b) => b ? gcd(b, a % b) : a
  for (let j = 1; j <= 6; j++) {
    for (let k = 1; k <= 6; k++) {
      if (j !== k && gcd(j, k) === 1) dp[1][j][k] = 1
    }
  }
  let ans = 0; const P = 1e9 + 7
  for (let i = 2; i < n; i++) {
    for (let j = 1; j <= 6; j++) {
      for (let k = 1; k <= 6; k++) {
        for (let l = 1; l <= 6; l++) {
          if (gcd(l, k) > 1) continue
          if (l === k || l === j) continue
          dp[i][k][l] = (dp[i][k][l] + dp[i - 1][j][k]) % P
        }
      }
    }
  }
  for (let j = 1; j <= 6; j++) {
    for (let k = 1; k <= 6; k++) {
      ans = (ans + dp[n - 1][j][k]) % P
    }
  }
  return ans
}
