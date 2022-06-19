/**
 * @param {number[]} forbidden
 * @param {number} a
 * @param {number} b
 * @param {number} x
 * @return {number}
 */
const minimumJumps = function (forbidden, a, b, x) {
  const q = [[0, 0, 0]]; const limit = Math.max(...forbidden, x) + b
  const s = new Set(forbidden); const v = {}
  while (q.length) {
    const [p, d, lastDir] = q.shift()
    if (v[`${p}_${lastDir}`]) continue
    v[`${p}_${lastDir}`] = 1
    if (p === x) return d
    if ((p <= limit || s.has(p - b)) && !s.has(p + a)) {
      q.push([p + a, d + 1, 1])
    }
    if (p - b >= 0 && lastDir !== -1 && !s.has(p - b)) {
      q.push([p - b, d + 1, -1])
    }
  }
  return -1
}
