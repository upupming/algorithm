/**
 * @param {number[][]} grid
 * @param {number} k
 * @return {number}
 dp[i][j][l] 模 k 为 l 的方案数量
 */
const numberOfPaths = function (g, k) {
  const m = g.length; const n = g[0].length; const P = 1e9 + 7
  const dp = Array(m).fill(0).map(() => Array(n).fill(0).map(() => Array(k).fill(0)))
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      for (let l = 0; l < k; l++) {
        if (i === 0 && j === 0) {
          if (l === (g[i][j] % k)) dp[i][j][l] = 1
          else dp[i][j][l] = 0
          continue
        }

        const l1 = ((l - g[i][j]) % k + k) % k
        let sum = 0
        if (i - 1 >= 0) sum += dp[i - 1][j][l1]
        if (j - 1 >= 0) sum += dp[i][j - 1][l1]
        // if (Number.isNaN(sum)) console.log(i, j, l, l1, dp[i][j-1][l1])
        dp[i][j][l] = sum % P
      }
    }
  }
  // console.log(dp)
  return dp[m - 1][n - 1][0]
}
