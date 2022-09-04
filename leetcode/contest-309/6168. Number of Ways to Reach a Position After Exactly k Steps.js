/**
 * @param {number} startPos
 * @param {number} endPos
 * @param {number} k
 * @return {number}
 */
const numberOfWays = function (startPos, endPos, k) {
  const dp = Array(2).fill(0).map(() => Array(2 * k + 1).fill(0))
  dp[0][startPos] = 1
  const P = 1e9 + 7
  for (let i = 1; i <= k; i++) {
    for (let p = startPos - k; p <= startPos + k; p++) {
      dp[1][p] = (dp[0][p - 1] ?? 0) + (dp[0][p + 1] ?? 0)
      dp[1][p] %= P
      // console.log(i, p, dp[i][p])
    }
    for (let p = startPos - k; p <= startPos + k; p++) {
      dp[0][p] = dp[1][p]
    }
  }
  return dp[1][endPos] ?? 0
}
