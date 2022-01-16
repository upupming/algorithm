/**
 * @param {number[][]} questions
 * @return {number}
 */
const mostPoints = function (q) {
  const n = q.length
  const dp = []
  dp[n] = 0
  for (let i = n - 1; i >= 0; i--) {
    const [p, b] = q[i]
    const j = i + b + 1
    dp[i] = Math.max(p + (j >= n ? 0 : dp[j]), dp[i + 1])
    // console.log(i, dp[i])
  }
  return dp[0]
}
