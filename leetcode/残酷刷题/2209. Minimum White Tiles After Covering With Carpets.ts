/*
dp[i][j] -> 前 i 个 floor，使用了 j 个 carpet 的最优答案
i 处用一个 carpet, dp[i-carpetLen][j-1]
i 处不用 carpet, dp[i-1][j]+(x)
*/
function minimumWhiteTiles (floor: string, numCarpets: number, carpetLen: number): number {
  const n = floor.length
  const dp: number[][] = Array(n + 1).fill(0).map(() => Array(numCarpets + 1).fill(1e10))
  for (let j = 0; j <= numCarpets; j++) dp[0][j] = 0
  for (let i = 1; i <= n; i++) {
    for (let j = 0; j <= numCarpets; j++) {
      dp[i][j] = Math.min(dp[i][j],
        dp[i - 1][j] + (floor[i - 1] === '1' ? 1 : 0)
      )
      if (j >= 1) {
        dp[i][j] = Math.min(dp[i][j],
          (i - carpetLen < 0) ? 0 : dp[i - carpetLen][j - 1])
      }
    }
  }
  return dp[n][numCarpets]
};
