/**
 * @param {number[]} nums
 * @return {number}
 */
const countDistinctIntegers = function (nums) {
  const s = new Set()
  for (const a of nums) {
    s.add(a)
    s.add(Number(a.toString().split('').reverse().join('')))
  }
  return s.size
}
