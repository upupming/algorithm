/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
const kInversePairs = function (n, k) {
  const f = Array(n + 1).fill(0).map(() => Array(k + 1).fill(0))
  f[0][0] = 1
  const get = (i, j) => {
    if (i < 0 || j < 0) return 0
    return f[i][j]
  }
  const P = 1e9 + 7
  for (let i = 1; i <= n; i++) {
    for (let j = 0; j <= k; j++) {
      f[i][j] = get(i, j - 1) - get(i - 1, j - i) + get(i - 1, j) + P
      f[i][j] %= P
    }
  }
  return f[n][k]
}
