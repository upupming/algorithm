/**
 * @param {number[]} slices
 * @return {number}
 */
const maxSizeSlices = function (s) {
  const n = s.length
  return Math.max(
    // 第 0 个不选
    solve(1, n - 1, n / 3),
    // 最后一个不选
    solve(0, n - 2, n / 3)
  )
  function solve (l, r, cnt) {
    // dp[i][j][k] 到 i 为止，选了 j 个的最大价值,k=0表示最后一个不选
    const dp = Array(r + 1).fill(0).map(() => Array(cnt + 1).fill(0).map(() => Array(2).fill(0)))
    dp[l][1][1] = s[l]

    for (let i = l + 1; i <= r; i++) {
      for (let j = 1; j <= Math.min(cnt, i - l + 1); j++) {
        dp[i][j][0] = Math.max(dp[i - 1][j][0], dp[i - 1][j][1])
        dp[i][j][1] = dp[i - 1][j - 1][0] + s[i]
      }
    }

    return Math.max(dp[r][cnt][0], dp[r][cnt][1])
  }
}
