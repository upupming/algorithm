/**
 * @param {number[]} nums
 * @param {number} original
 * @return {number}
 */
const findFinalValue = function (nums, o) {
  const s = new Set(nums)
  while (s.has(o)) o *= 2
  return o
}
