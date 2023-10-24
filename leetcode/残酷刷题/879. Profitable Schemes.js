/**
 * @param {number} n
 * @param {number} minProfit
 * @param {number[]} group
 * @param {number[]} profit
 * @return {number}
 dp[i][j][k]
 前 i 组，人数为 j，利润为 k 的方案总数
 dp[i-1][j-group[i]][k-profit[i]]
 dp[i-1][j][k]
 */
const profitableSchemes = function (n, minProfit, group, profit) {
  const P = 1e9 + 7; const m = group.length
  const dp = Array(m + 1).fill(0).map(() => Array(n + 1).fill(0).map(() => Array(minProfit + 1).fill(0)))
  let ans = 0
  dp[0][0][0] = 1
  for (let i = 0; i < m; i++) {
    for (let j = 0; j <= n; j++) {
      for (let k = 0; k <= minProfit; k++) {
        dp[i + 1][j][k] += dp[i][j][k]
        dp[i + 1][j][k] %= P

        if (j + group[i] <= n) {
          dp[i + 1][j + group[i]][Math.min(minProfit, k + profit[i])] += dp[i][j][k]
          dp[i + 1][j + group[i]][Math.min(minProfit, k + profit[i])] %= P
        }
      }
    }
  }
  for (let j = 0; j <= n; j++) ans = (ans + dp[m][j][minProfit]) % P
  return ans
}
