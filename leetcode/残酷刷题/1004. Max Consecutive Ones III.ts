function longestOnes (nums: number[], k: number): number {
  const n = nums.length
  const cnt = [0, 0]
  let ans = 0
  for (let i = 0, j = 0; i < n; i++) {
    while (j < n && cnt[0] + (nums[j] === 0 ? 1 : 0) <= k) {
      cnt[0] += nums[j] === 0 ? 1 : 0
      j++
    }
    ans = Math.max(ans, j - i)
    cnt[0] -= nums[i] === 0 ? 1 : 0
  }
  return ans
};
