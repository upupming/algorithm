/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
 var longestIdealString = function(s, k) {
  const n = s.length
  const dp = Array(n).fill(0)
  const max = Array(26).fill(0)
  for (let i = 0; i < n; i++) {
      const c = s.charCodeAt(i) - 'a'.charCodeAt(0)
      for (let j = Math.max(0, c-k); j < Math.min(26, c+k+1); j++) {
          dp[i] = Math.max(dp[i], max[j] + 1)
          // console.log(i, j, max[j], dp[i])
      }
      max[c] = Math.max(max[c], dp[i])
  }
  return Math.max(...max)
};
