/*
 * @lc app=leetcode id=1674 lang=typescript
 *
 * [1674] Minimum Moves to Make Array Complementary
 * https://www.bilibili.com/video/BV1L64y1f7J9/
 * 多个（每一对）差分数组合并成一个总的（总操作次数）差分数组
 */

// @lc code=start
function minMoves (nums: number[], limit: number): number {
  const diff = Array<number>(2e5 + 10).fill(0)
  const n = nums.length
  for (let i = 0; i < n / 2; i++) {
    const [a, b] = [Math.min(nums[i], nums[n - 1 - i]), Math.max(nums[i], nums[n - 1 - i])]

    diff[2] += 2
    diff[a + 1] -= 1
    diff[a + b] -= 1
    diff[a + b + 1] += 1
    diff[limit + b + 1] += 1
  }
  let ans = 1e12
  for (let sum = 2; sum <= 2 * limit; sum++) {
    diff[sum] += diff[sum - 1]
    ans = Math.min(ans, diff[sum])
  }
  return ans
};
// @lc code=end
