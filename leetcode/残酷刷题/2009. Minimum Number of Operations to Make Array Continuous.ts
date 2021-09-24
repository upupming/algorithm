function minOperations (nums: number[]): number {
  const n = nums.length
  const a = [...new Set(nums)].sort((a, b) => a - b)
  const m = a.length
  let ans = 1e6
  for (let i = 0, j = 0; i < m; i++) {
    while (j < m && a[j] - a[i] <= n - 1) j++
    ans = Math.min(ans, n - (j - i))
  }
  return ans
};
