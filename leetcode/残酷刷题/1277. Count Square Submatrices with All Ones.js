/**
 * @param {number[][]} matrix
 * @return {number}
 */
const countSquares = function (matrix) {
  const m = matrix.length; const n = matrix[0].length
  const dp = [...Array(m)].map(() => [])
  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (matrix[i][j] === 1) {
        dp[i][j] = Math.min(dp[i - 1]?.[j] ?? 0, dp[i]?.[j - 1] ?? 0, dp[i - 1]?.[j - 1] ?? 0) + 1
        ans += dp[i][j]
      } else { dp[i][j] = 0 }
    }
  }
  return ans
}
