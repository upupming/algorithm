/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const constrainedSubsetSum = function (nums, k) {
  const n = nums.length
  const q = [[-1e10, -1]]; const dp = Array(n + 1).fill(0); let ans = -1e10
  for (let i = 0; i < n; i++) {
    // 区间长度超过 k，去掉
    while (q.length && i - q[0][1] > k) q.shift()

    dp[i] = Math.max(0, q[0][0]) + nums[i]
    ans = Math.max(ans, dp[i])

    // 远的，还小就要去掉
    while (q.length && q[q.length - 1][0] <= dp[i]) q.pop()
    q.push([dp[i], i])
  }
  return ans
}
