/**
 * @param {number} m
 * @param {number} n
 * @param {number[][]} prices
 * @return {number}
 */
const sellingWood = function (m, n, ps) {
  const f = Array(m + 1).fill(0).map(() => Array(n + 1).fill(0))
  for (const [h, w, p] of ps) {
    f[h][w] = p
  }
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      for (let k = 1; k <= i; k++) f[i][j] = Math.max(f[i][j], f[k][j] + f[i - k][j])
      for (let k = 1; k <= j; k++) f[i][j] = Math.max(f[i][j], f[i][k] + f[i][j - k])
    }
  }
  return f[m][n]
}
