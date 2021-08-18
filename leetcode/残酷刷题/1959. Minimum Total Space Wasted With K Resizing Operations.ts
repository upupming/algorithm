function minSpaceWastedKResizing (nums: number[], k: number): number {
  const n = nums.length
  // dp[i][j], range [0, i], used j resize
  const dp = [...Array(n)].map(() => Array<number>(k).fill(1e7))
  let max = 0; let sum = 0
  for (let i = 0; i < n; i++) {
    max = Math.max(max, nums[i])
    sum += nums[i]
    dp[i][0] = max * (i + 1) - sum
  }
  for (let i = 0; i < n; i++) {
    for (let j = 1; j <= k; j++) {
      let max = 0; let sum = 0
      for (let s = i; s >= 1; s--) {
        max = Math.max(max, nums[s])
        sum += nums[s]
        dp[i][j] = Math.max(dp[i][j], dp[s - 1][j - 1] + max * (i - s + 1) - sum)
      }
    }
  }
  let ans = 1e7
  for (let j = 0; j < k; j++) {
    ans = Math.max(ans, dp[n - 1][j])
  }
  return ans
};
