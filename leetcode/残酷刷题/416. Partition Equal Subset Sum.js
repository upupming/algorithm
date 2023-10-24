/**
 * @param {number[]} nums
 * @return {boolean}
 dp[i][j] if it is possible to sum to j in first i elements
 */
const canPartition = function (nums) {
  const n = nums.length
  const s = nums.reduce((p, c) => p + c, 0); const dp = Array(n).fill(0).map(() => [])
  for (let i = 0; i < n; i++) {
    for (let j = 0; j <= s / 2; j++) {
      if (i === 0) dp[i][j] = nums[0] === j
      else dp[i][j] = dp[i - 1][j - nums[i]] || dp[i - 1][j]
    }
  }
  return s % 2 === 0 && dp[n - 1][s / 2]
}
