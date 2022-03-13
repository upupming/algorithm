/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const maximumTop = function (nums, k) {
  const n = nums.length
  if (k <= n) {
    return Math.max(max(nums, k - 1), nums[k] ?? -1)
  } else if (k <= 2 * n) {
    return Math.max(max(nums, n))
  } else {
    if (n === 1 && k % 2 == 1) return -1
    return Math.max(max(nums, n))
  }

  function max (nums, t) {
    let ans = -1
    for (let i = 0; i < t; i++) {
      ans = Math.max(ans, nums[i])
    }
    return ans
  }
}
