/**
 * @param {number} n
 * @return {number}
 */
 var countHousePlacements = function(n) {
  const dp = [], P = 1e9 + 7
  dp[0] = [1, 0]
  for (let i = 1; i <= n; i++) {
      dp[i] = []
      // i 处不放房子
      dp[i][0] = (dp[i-1][0] + dp[i-1][1]) % P
      // i 处放房子
      dp[i][1] = dp[i-1][0] % P
  }
  const x = BigInt((dp[n][0] + dp[n][1]) % P)
  return (x * x) % BigInt(P)
};
