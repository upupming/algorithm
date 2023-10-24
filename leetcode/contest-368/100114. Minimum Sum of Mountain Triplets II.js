/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumSum = function (nums) {
  const n = nums.length; let ans = 1e10
  const minA = Array(n).fill(1e10); const minB = Array(n).fill(1e10)
  minA[-1] = 1e10, minB[n] = 1e10
  for (let i = 0; i < n; i++) minA[i] = Math.min(nums[i], minA[i - 1])
  for (let i = n - 1; i >= 0; i--) minB[i] = Math.min(nums[i], minB[i + 1])
  // console.log(minA, minB)
  for (let i = 1; i < n - 1; i++) {
    const a = minA[i - 1]; const b = minB[i + 1]
    if (a < nums[i] && b < nums[i]) ans = Math.min(ans, a + nums[i] + b)
  }
  return ans === 1e10 ? -1 : ans
}
