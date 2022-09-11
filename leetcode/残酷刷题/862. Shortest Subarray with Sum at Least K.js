/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const shortestSubarray = function (nums, k) {
  const n = nums.length
  const sum = [0]; const q = [0]; let ans = 1e10
  for (let i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + nums[i - 1]
    // 尽量短
    while (q.length && sum[i] - sum[q[1]] >= k) q.shift()
    if (sum[i] - sum[q[0]] >= k) ans = Math.min(i - q[0], ans)
    while (q.length && sum[q[q.length - 1]] >= sum[i]) q.pop()
    q.push(i)
  }
  return ans === 1e10 ? -1 : ans
}
