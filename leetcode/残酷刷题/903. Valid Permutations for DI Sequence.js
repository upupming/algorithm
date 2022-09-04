/**
 * @param {string} s
 * @return {number}
 */
const numPermsDISequence = function (s) {
  const n = s.length; const P = 1e9 + 7
  s = '#' + s
  const dp = Array(n + 1).fill(0).map(() => Array(n + 1).fill(0))
  dp[0][0] = 1
  // dp[i][j] 表示 0~i 的满足题目条件的排列组合，且最后一位为 j 的方案数目
  for (let i = 1; i <= n; i++) {
    for (let j = 0; j <= i; j++) {
      if (s[i] === 'I') {
        for (let k = 0; k < j; k++) {
          dp[i][j] += dp[i - 1][k]
          dp[i][j] %= P
        }
      } else {
        for (let k = j; k <= i - 1; k++) {
          dp[i][j] += dp[i - 1][k]
          dp[i][j] %= P
        }
      }
    }
  }
  let ans = 0
  for (let i = 0; i <= n; i++) ans = (ans + dp[n][i]) % P
  return ans
}
