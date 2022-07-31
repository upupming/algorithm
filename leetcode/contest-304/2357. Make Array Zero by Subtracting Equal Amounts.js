/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumOperations = function (nums) {
  const n = nums.length
  let ok = true; let min = 1e10
  for (let i = 0; i < n; i++) {
    if (nums[i] > 0) {
      ok = false
      min = Math.min(min, nums[i])
    }
  }
  if (ok) return 0
  return minimumOperations(nums.map(x => x - min)) + 1
}
