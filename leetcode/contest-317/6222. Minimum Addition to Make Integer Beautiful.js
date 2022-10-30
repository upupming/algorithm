/**
 * @param {number} n
 * @param {number} target
 * @return {number}
 */
const makeIntegerBeautiful = function (n, target) {
  const a = String(n).split('').map(Number)
  const m = a.length
  const sum = a.reduce((p, c) => p + c, 0)
  if (sum <= target) return 0
  let tmp = 0; let bs = 0
  for (let i = 0; i < m; i++) {
    const j = m - 1 - i
    tmp += a[j] * Math.pow(10, i)
    bs += a[j]
    const t = Math.pow(10, i + 1)
    if (sum - bs + 1 <= target) {
      return t - tmp
    }
  }
}
