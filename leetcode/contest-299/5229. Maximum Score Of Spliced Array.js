/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
 var maximumsSplicedArray = function(a1, a2) {
  function solve(a1, a2) {
      const n = a1.length, d = [], dp = []
      dp[-1] = 0
      let max = -1e10, sum = 0
      for (let i = 0; i < n; i++) {
          d[i] = a2[i] - a1[i]
          sum += a1[i]
          dp[i] = Math.max(dp[i-1], 0) + d[i]
          max = Math.max(max, dp[i])
      }
      if (max > 0) sum += max
      return sum
  }

  return Math.max(solve(a1, a2), solve(a2, a1))
};
