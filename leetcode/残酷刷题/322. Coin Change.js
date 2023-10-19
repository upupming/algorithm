/**
 * @param {number[]} coins
 * @param {number} amount
 * @return {number}
 */
const coinChange = function (coins, amount) {
  const n = coins.length; const dp = Array(amount + 1).fill(1e10)
  dp[0] = 0
  for (let i = 1; i <= amount; i++) {
    for (const c of coins) {
      if (i - c >= 0) { dp[i] = Math.min(dp[i], dp[i - c] + 1) }
    }
  }
  return dp[amount] === 1e10 ? -1 : dp[amount]
}
