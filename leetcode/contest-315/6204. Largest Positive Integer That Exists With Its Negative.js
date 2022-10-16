/**
 * @param {number[]} nums
 * @return {number}
 */
const findMaxK = function (nums) {
  let k = -1
  const s = new Set([...nums])
  for (const a of s) {
    if (a > 0 && a > k && s.has(-a)) k = a
  }
  return k
}
