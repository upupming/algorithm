/**
 * @param {number[]} nums
 * @return {number}
 */
 var rob = function(nums) {
  if (nums.length === 1) return nums[0]
  const n = nums.length
  // dp[i][j][k] j 表示第 i 个有没有被 rob
  // k 表示第 1 个有没有被 rob
  const dp = Array(n).fill(0).map(() => Array(2).fill(0).map(() => Array(2).fill(0)))
  dp[0][0][0] = 0, dp[0][0][1] = -1
  dp[0][1][0] = -1, dp[0][1][1] = nums[0]
  for (let i = 1; i < n; i++) {
      dp[i][0][0] = Math.max(dp[i-1][1][0], dp[i-1][0][0])
      dp[i][0][1] = Math.max(dp[i-1][1][1], dp[i-1][0][1])

      dp[i][1][0] = Math.max(dp[i-1][0][0], 0) + nums[i]
      dp[i][1][1] = Math.max(dp[i-1][0][1], 0) + nums[i]
  }
  return Math.max(dp[n-1][0][0], dp[n-1][0][1], dp[n-1][1][0])
};
