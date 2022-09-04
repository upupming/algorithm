/**
 * @param {number[]} nums
 * @param {number} limit
 * @return {number}
 */
const longestSubarray = function (nums, limit) {
  const n = nums.length; let ans = 0; const qMin = [[1e10, -1]]; const qMax = [[-1e10, -1]]
  for (let i = 0, j = 0; i < n; i++) {
    while ((qMin[0][0] === 1e10 || qMax[0][0] === -1e10 || Math.abs(qMax[0][0] - qMin[0][0]) <= limit)) {
      ans = Math.max(ans, j - i)
      if (j === n) break
      while (qMax.length && qMax[qMax.length - 1][0] <= nums[j]) qMax.pop()
      while (qMin.length && qMin[qMin.length - 1][0] >= nums[j]) qMin.pop()
      qMax.push([nums[j], j])
      qMin.push([nums[j], j])
      j++
    }

    while (qMin.length && qMin[0][1] <= i) qMin.shift()
    while (qMin.length && qMax[0][1] <= i) qMax.shift()
  }
  return ans
}
