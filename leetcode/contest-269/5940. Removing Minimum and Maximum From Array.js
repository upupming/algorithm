/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumDeletions = function (nums) {
  let min = Infinity; let max = -Infinity; const n = nums.length
  for (let i = 0; i < n; i++) {
    min = Math.min(min, nums[i])
    max = Math.max(max, nums[i])
  }
  const i = nums.indexOf(min); const j = nums.indexOf(max)
  const mi = Math.min(i, j); const ma = Math.max(i, j)
  return Math.min(
    Math.max(i + 1, j + 1),
    Math.max(n - i, n - j),
    mi + 1 + n - ma
  )
}
