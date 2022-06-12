/**
 * @param {number[][]} grid
 * @param {number[][]} moveCost
 * @return {number}
 */
 var minPathCost = function(g, mc) {
  const m = g.length, n = g[0].length
  const dp = Array(m).fill(0).map(() => [])
  for (let i = 0; i < n; i++) dp[0][i] = g[0][i]
  let ans = 1e10
  for (let i = 1; i < m; i++) {
      for (let j = 0; j < n; j++) {
          dp[i][j] = 1e10
          for (let k = 0; k < n; k++) {
              dp[i][j] = Math.min(dp[i][j], dp[i-1][k] + mc[g[i-1][k]][j] + g[i][j])
          }
          if (i === m-1) ans = Math.min(ans, dp[i][j])
      }
  }
  return ans
};
