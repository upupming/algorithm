/**
 * @param {number[]} nums
 * @return {void} Do not return anything, modify nums in-place instead.
 197 3 8642
 197 4 2368
 */
const nextPermutation = function (nums) {
  const n = nums.length
  let i = n - 1
  while (i > 0 && nums[i] <= nums[i - 1]) {
    i--
  }
  // 特殊情况，321，直接反转
  if (i === 0) return nums.reverse()
  // nums[i] > nums[i-1]
  i--
  let j = n - 1
  while (nums[j] <= nums[i]) j--
  [nums[j], nums[i]] = [nums[i], nums[j]]
  // reverse
  for (let k1 = i + 1, k2 = n - 1; k1 < k2; k1++, k2--) {
    [nums[k1], nums[k2]] = [nums[k2], nums[k1]]
  }
  return nums
}
