/**
 * @param {character[][]} matrix
 * @return {number}
 */
const maximalRectangle = function (g) {
  const m = g.length; const n = g[0].length
  const f = Array(n).fill(0)
  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      f[j] = (g[i][j] === '0') ? 0 : (f[j] + 1)
    }
    f[-1] = -1, f[n] = -1
    const l = []; const r = []
    let s = [-1]
    for (let i = 0; i < n; i++) {
      while (f[s[s.length - 1]] >= f[i]) s.pop()
      l[i] = s[s.length - 1]
      s.push(i)
    }
    s = [n]
    for (let i = n - 1; i >= 0; i--) {
      while (f[s[s.length - 1]] >= f[i]) s.pop()
      r[i] = s[s.length - 1]
      s.push(i)
    }
    for (let i = 0; i < n; i++) {
      ans = Math.max(ans, f[i] * (r[i] - l[i] - 1))
    }
  }
  return ans
}
