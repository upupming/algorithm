/**
 * @param {number} amount
 * @param {number[]} coins
 * @return {number}
 */
var change = function(amount, coins) {
    const n = coins.length, dp = Array(amount+1).fill(0).map(() => Array(n).fill(0))
    dp[0][0] = 1
    if (amount === 0) return 1
    for (let i = 1; i <= amount; i++) {
        let s = 0
        for (let j = 0; j < n; j++) {
            if (i >= coins[j]) {
                // 硬币递增，避免重复计算
                for (let k = 0; k <= j; k++) {
                    dp[i][j] += dp[i-coins[j]][k]
                }
            }
            s += dp[i][j]
        }
        if (i === amount) return s
    }
  };
