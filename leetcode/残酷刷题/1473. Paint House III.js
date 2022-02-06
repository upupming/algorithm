/**
 * @param {number[]} houses
 * @param {number[][]} cost
 * @param {number} m
 * @param {number} n
 * @param {number} target
 * @return {number}
 */
const minCost = function (houses, cost, m, n, target) {
  const dp = [...Array(m + 1)].map(() => Array(target + 1).fill(0).map(() => Array(n + 1).fill(1e10)))

  for (let k = 0; k <= n; k++) dp[0][0][k] = 0

  // dp[i][j][k] 表示前i个房子构成了j个block，并且第i个房子喷涂的颜色是k的最小代价
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= target; j++) {
      if (houses[i - 1] !== 0) {
        // 颜色无法更改
        const k = houses[i - 1]
        for (let l = 1; l <= n; l++) {
          if (k === l) {
            // 合并为一个 block
            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][j][k])
          } else {
            // 只能新建一个 block
            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][j - 1][l])
          }
        }
      } else {
        // 可以涂想要的颜色，枚举涂成的所有颜色
        for (let k = 1; k <= n; k++) {
          for (let l = 1; l <= n; l++) {
            if (k === l) {
              // 合并为一个 block
              dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][j][k] + cost[i - 1][k - 1])
            } else {
              // 只能新建一个 block
              dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][j - 1][l] + cost[i - 1][k - 1])
            }
          }
        }
      }
    }
  }

  let ans = dp[m][target].reduce((p, c) => Math.min(p, c), 1e10)
  if (ans === 1e10) ans = -1
  return ans
}
