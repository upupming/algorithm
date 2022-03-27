/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const maximumTop = function (nums, k) {
  const n = nums.length
  let ans = -1
  for (let i = 0; i < n; i++) {
    const r = k - i
    let ok = 0
    if (r < 0) continue
    else if (r === 0) ok = 1
    else if (r === 1) ok = 0
    else if (r % 2 === 0) ok = 1
    else if (i + 1 < n || i - 1 >= 0) ok = 1
    if (ok) ans = Math.max(ans, nums[i])
  }
  return ans
}
