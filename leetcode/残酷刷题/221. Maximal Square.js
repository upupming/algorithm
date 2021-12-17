/**
 * @param {character[][]} matrix
 * @return {number}
 */
const maximalSquare = function (ma) {
  const m = ma.length; const n = ma[0].length
  const sum = [...Array(m + 1)].map(() => Array(n + 1).fill(0))
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + Number(ma[i - 1][j - 1])
    }
  }
  let ans = 0
  for (let i0 = 1; i0 <= m; i0++) {
    for (let j0 = 1; j0 <= n; j0++) {
      for (let i1 = i0; i1 <= m; i1++) {
        const j1 = j0 + i1 - i0
        const area = sum[i1][j1] - sum[i1][j0 - 1] - sum[i0 - 1][j1] + sum[i0 - 1][j0 - 1]
        if (area === (i1 - i0 + 1) * (j1 - j0 + 1)) {
          // console.log(i0, j0, i1, j1, area)
          ans = Math.max(ans, area)
        }
      }
    }
  }
  return ans
}
