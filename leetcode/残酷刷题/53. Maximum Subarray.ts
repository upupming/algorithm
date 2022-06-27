function maxSubArray (nums: number[]): number {
  const n = nums.length
  const f = Array(n + 1).fill(0)
  let ans = -1e10
  for (let i = 1; i <= n; i++) {
    f[i] = Math.max(f[i - 1], 0) + nums[i - 1]
    ans = Math.max(ans, f[i])
  }
  return ans
};
