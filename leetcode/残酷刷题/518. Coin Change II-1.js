/**
 * @param {number} amount
 * @param {number[]} coins
 * @return {number}
 */
var change = function(amount, coins) {
  const n = coins.length, dp = Array(amount+1).fill(0)
  dp[0] = 1
  if (amount === 0) return 1
  for (let j = 0; j < n; j++) {
      for (let i = 1; i <= amount; i++) {
          if (i >= coins[j]) dp[i] += dp[i-coins[j]]
      }
  }
  return dp[amount]
};
