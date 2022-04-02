/**
 * @param {number[]} nums
 * @return {number}
 */
var triangularSum = function (nums, l, r) {
  const n = nums.length
  l ??= 0, r ??= n - 1
  if (l >= r) return nums[l]
  for (let i = l; i < r; i++) {
    nums[i] = (nums[i] + nums[i + 1]) % 10
  }
  return triangularSum(nums, l, r - 1)
}
