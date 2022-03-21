/**
 * @param {number[]} nums
 * @return {number}
 */
const countHillValley = function (nums) {
  const n = nums.length
  let ans = 0
  for (let i = 0; i < n; i++) {
    if (i > 0 && nums[i] === nums[i - 1]) continue
    let j = i - 1; let k = i + 1
    while (j > 0 && nums[j] === nums[i]) j--
    while (k < n && nums[k] === nums[i]) k++
    if (j < 0 && k >= n) continue
    if (nums[j] < nums[i] && nums[k] < nums[i]) ans++
    if (nums[j] > nums[i] && nums[k] > nums[i]) ans++
  }
  return ans
}
