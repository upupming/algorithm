function increasingTriplet (nums: number[]): boolean {
  const n = nums.length
  const min = []; const max = []
  min[-1] = 1e10, max[n] = -1e10
  for (let i = 0; i < n; i++) {
    min[i] = Math.min(min[i - 1], nums[i])
  }
  for (let i = n - 1; i >= 0; i--) {
    max[i] = Math.max(max[i + 1], nums[i])
  }
  for (let i = 0; i < n; i++) {
    if (min[i - 1] < nums[i] && nums[i] < max[i + 1]) return true
  }
  return false
};
