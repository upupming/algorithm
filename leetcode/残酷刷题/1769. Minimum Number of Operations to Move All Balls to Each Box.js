/**
 * @param {string} boxes
 * @return {number[]}
 */
const minOperations = function (b) {
  const n = b.length; let s = 0; let m = 0
  for (let i = 0; i < n; i++) {
    if (b[i] === '1') {
      m++
      s += i
    }
  }
  const ans = []; let t = 0; let o = 0
  for (let i = 0; i < n; i++) {
    if (b[i] === '1') {
      o++
      t += i
    }
    const u = s - t; const p = m - o
    ans[i] = (o * i - t) + (u - p * i)
  }
  return ans
}
