/**
 * @param {number[]} nums
 * @return {number}
 */
const maximumDifference = function (nums) {
  let ans = -1; const n = nums.length
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      if (nums[i] < nums[j]) ans = Math.max(ans, nums[j] - nums[i])
    }
  }
  return ans
}
