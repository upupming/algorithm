/**
 * @param {number[]} nums
 * @param {number[]} target
 * @return {number}
 */
const makeSimilar = function (nums, target) {
  const a1 = nums.filter(x => x % 2 === 1).sort((a, b) => a - b)
  const a2 = nums.filter(x => x % 2 === 0).sort((a, b) => a - b)
  const b1 = target.filter(x => x % 2 === 1).sort((a, b) => a - b)
  const b2 = target.filter(x => x % 2 === 0).sort((a, b) => a - b)
  let ans = 0
  for (let i = 0; i < a1.length; i++) {
    ans += Math.abs(a1[i] - b1[i]) / 2
  }
  for (let i = 0; i < a2.length; i++) {
    ans += Math.abs(a2[i] - b2[i]) / 2
  }
  return ans / 2
}
