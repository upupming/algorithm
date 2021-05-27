/*
 * @lc app=leetcode id=995 lang=typescript
 *
 * [995] Minimum Number of K Consecutive Bit Flips
 * 贪心，能翻尽翻，如果存在一种方案的话，按照起始元素递增的顺序一定是可以的
 * 时间复杂度: O(nk)
 * 利用前缀和可以优化成 O(n) 的
 */

// @lc code=start
function minKBitFlips (nums: number[], k: number): number {
  const n = nums.length
  const flippedDiff = Array<number>(n).fill(0)
  let [flipped, ans] = [0, 0]
  for (let i = 0; i < n; i++) {
    flipped += flippedDiff[i]
    if (((flipped % 2 === 1) ? 1 - nums[i] : nums[i]) === 0) {
      const j = i + k - 1
      if (j >= n) return -1
      flippedDiff[i] += 1
      flipped += 1
      flippedDiff[j + 1] -= 1
      ans++
    }
  }
  return ans
};
// @lc code=end
