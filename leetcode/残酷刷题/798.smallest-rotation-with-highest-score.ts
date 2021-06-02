/*
 * @lc app=leetcode id=798 lang=typescript
 *
 * [798] Smallest Rotation with Highest Score
 */

// @lc code=start
function bestRotation (nums: number[]): number {
  const n = nums.length
  const diff = Array<number>(n + 1).fill(0)
  for (let i = 0; i < n; i++) {
    if (nums[i] <= i) {
      diff[0] += 1
      diff[i - (nums[i] - 1)] -= 1
      diff[i + 1] += 1
    } else {
      diff[0] += 0
      diff[i + 1] += 1
      diff[i + 1 + n - nums[i]] -= 1
    }
  }
  let maxScore = diff[0]; let maxK = 0
  for (let k = 1; k < n; k++) {
    diff[k] += diff[k - 1]
    if (diff[k] > maxScore) {
      maxK = k
      maxScore = diff[k]
    }
  }
  return maxK
};
// @lc code=end
