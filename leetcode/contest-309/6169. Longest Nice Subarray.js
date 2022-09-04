/**
 * @param {number[]} nums
 * @return {number}
 */
const longestNiceSubarray = function (nums) {
  const n = nums.length
  let xor = 0; let ans = 0
  for (let i = 0, j = 0; i < n; i++) {
    while (j < n && ((nums[j] & xor) === 0)) xor += nums[j], j++
    ans = Math.max(ans, j - i)

    xor -= nums[i]
  }
  return ans
}
