/**
 * @param {number[]} jobs
 * @param {number} k
 * @return {number}
 */
const minimumTimeRequired = function (jobs, k) {
  const n = jobs.length
  const cache = {}
  const time = (i) => {
    if (cache[i] != null) return cache[i]
    let ans = 0
    for (let k = 0; k < n; k++) {
      if (i >> k & 1) ans += jobs[k]
    }
    return cache[i] = ans
  }
  const dp = Array(k + 1).fill(0).map(() => Array(1 << n).fill(1e10))
  dp[0][0] = 0
  for (let i = 1; i <= k; i++) {
    dp[i][0] = 0
    for (let j = 1; j < 1 << n; j++) {
      // j 的所有子集
      for (let k = j; ; k = (k - 1) & j) {
        dp[i][j] = Math.min(
          dp[i][j],
          Math.max(dp[i - 1][j - k], time(k))
        )
        if (k === 0) break
      }
    }
  }
  return dp[k][(1 << n) - 1]
}
