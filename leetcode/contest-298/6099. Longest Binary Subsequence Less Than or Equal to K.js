/**
 * @param {string} s
 * @param {number} k
 * @return {number}

dp[i][j] 以 i 结尾长度为 j 的最小值
dp[i][j] <= k, ans = max(ans, j)
dp[0...i-1][j-1]
 */
const longestSubsequence = function (s, k) {
  const n = s.length; const dp = Array(n + 1).fill(0).map(() => Array(n + 1).fill(1e10))
  s = ' ' + s
  let ans = 0
  let min = Array(n + 1).fill(1e10)
  min[0] = 0
  for (let i = 1; i <= n; i++) {
    // 长度为 0 的值都为 0
    dp[i][0] = 0
    const next_min = [...min]
    for (let j = 1; j <= i; j++) {
      // for (let l = 0; l < i; l++) {
      //     dp[i][j] = Math.min(dp[i][j], dp[l][j-1]*2 + Number(s[i]))
      // }
      // console.log(i, j, dp[i][j])
      dp[i][j] = Math.min(dp[i][j], min[j - 1] * 2 + Number(s[i]))
      if (dp[i][j] <= k) ans = Math.max(ans, j)
      next_min[j] = Math.min(next_min[j], dp[i][j])
    }
    min = next_min
  }
  return ans
}
