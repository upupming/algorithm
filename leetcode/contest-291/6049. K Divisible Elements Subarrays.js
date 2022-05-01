/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} p
 * @return {number}
 */
const countDistinct = function (nums, k, p) {
  const n = nums.length
  const s = new Set()
  for (let i = 0; i < n; i++) {
    for (let j = i; j < n; j++) {
      let tmp = ''; let cnt = 0
      for (let k = i; k <= j; k++) {
        tmp += `_${nums[k]}`
        cnt += nums[k] % p === 0
      }
      if (cnt <= k) { s.add(tmp) }
    }
  }
  // console.log(s)
  return s.size
}
