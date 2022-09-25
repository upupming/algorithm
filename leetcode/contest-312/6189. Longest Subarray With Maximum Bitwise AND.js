/**
 * @param {number[]} nums
 * @return {number}
 */
const longestSubarray = function (nums) {
  const max = Math.max(...nums)
  let maxLen = 0
  const n = nums.length
  for (let i = 0; i < n; i++) {
    let j = i
    while (j < n && nums[j] === nums[i]) j++
    if (nums[i] === max) {
      const len = j - i
      maxLen = Math.max(maxLen, len)
    }
    i = j - 1
  }
  return maxLen
}
