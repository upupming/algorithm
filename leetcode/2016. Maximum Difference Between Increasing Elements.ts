function maximumDifference (nums: number[]): number {
  const max = [-1]; const n = nums.length
  for (let i = n - 1; i >= 0; i--) {
    max.push(Math.max(max[max.length - 1], nums[i]))
  }
  max.reverse()
  let ans = -1
  for (let i = 0; i < n; i++) {
    if (max[i + 1] > nums[i]) {
      ans = Math.max(max[i + 1] - nums[i], ans)
    }
  }
  return ans
};
