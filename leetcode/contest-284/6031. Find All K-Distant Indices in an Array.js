/**
 * @param {number[]} nums
 * @param {number} key
 * @param {number} k
 * @return {number[]}
 */
const findKDistantIndices = function (nums, key, k) {
  const ans = []
  for (let i = 0; i < nums.length; i++) {
    let ok = false
    for (let j = 0; j < nums.length; j++) {
      if (nums[j] === key && Math.abs(i - j) <= k) {
        ok = true
        break
      }
    }
    if (ok) ans.push(i)
  }
  return ans
}
