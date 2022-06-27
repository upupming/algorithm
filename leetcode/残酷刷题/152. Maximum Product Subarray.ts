function maxProduct (nums: number[]): number {
  const n = nums.length
  // f[i][0]: max, f[i][1]: min; both ends with nums[i], as neg multiply neg can be pos
  const f: number[][] = Array(n + 1).fill(0).map(() => [])
  f[0][0] = f[0][1] = 1
  let ans = -1e10
  for (let i = 1; i <= n; i++) {
    f[i][0] = Math.max(f[i - 1][0] * nums[i - 1], f[i - 1][1] * nums[i - 1], nums[i - 1])
    f[i][1] = Math.min(f[i - 1][0] * nums[i - 1], f[i - 1][1] * nums[i - 1], nums[i - 1])
    ans = Math.max(ans, f[i][0])
  }
  return ans
};
