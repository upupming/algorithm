/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumSum = function (nums) {
  const n = nums.length
  let ans = 1e10
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      for (let k = j + 1; k < n; k++) {
        if (nums[i] < nums[j] && nums[j] > nums[k]) ans = Math.min(ans, nums[i] + nums[j] + nums[k])
      }
    }
  }
  return ans === 1e10 ? -1 : ans
}
