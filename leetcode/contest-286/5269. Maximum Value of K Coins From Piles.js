/**
 * @param {number[][]} piles
 * @param {number} k
 * @return {number}

 i: 1e3
 k: 2e3

 dp[i][k] = dp[i-1][j] + 在 i 中选 k-j 个元素

 */
const maxValueOfCoins = function (pl, K) {
  const n = pl.length

  const sum = []
  for (let i = 0; i < pl.length; i++) {
    sum[i] = [], sum[i][-1] = 0
    for (let j = 0; j < pl[i].length; j++) {
      sum[i][j] = sum[i][j - 1] + pl[i][j]
    }
  }
  const dp = Array(n).fill(0).map(() => Array(K + 1).fill(0))
  dp[-1] = []
  for (let i = 0; i <= K; i++) dp[-1][i] = 0

  for (let i = 0; i < n; i++) {
    for (let k = 0; k <= K; k++) {
      // 由于 sum(piles[i].length) == 2e3，第一层循环和第三层循环总时间复杂度才是 2e3
      for (let j = 0; j <= pl[i].length; j++) {
        if (j > k) break
        dp[i][k] = Math.max(dp[i][k], dp[i - 1][k - j] + sum[i][j - 1])
        // console.log(i, k, j, dp[i-1][k-j], sum[i][j-1], dp[i][k])
      }
    }
  }

  return dp[n - 1][K]
}
/*
[[37,88],[51,64,65,20,95,30,26],[9,62,20],[44]]
9

494
*/
