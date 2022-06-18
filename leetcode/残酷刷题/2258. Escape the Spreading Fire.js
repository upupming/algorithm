/**
 * @param {number[][]} grid
 * @return {number}
 */
const maximumMinutes = function (g) {
  const m = g.length; const n = g[0].length
  const fs = []
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (g[i][j] === 1) fs.push([i, j])
    }
  }
  const p = bfs([[0, 0]]); const f = bfs(fs)
  if (p[m - 1][n - 1] === 1e10) return -1
  if (f[m - 1][n - 1] === 1e10) return 1e9
  if (p[m - 1][n - 1] > f[m - 1][n - 1]) return -1
  const D = f[m - 1][n - 1] - p[m - 1][n - 1]
  if (getDirection(f) === 'both') return D - 1
  if (getDirection(f) === getDirection(p)) return D - 1
  return D

  function getDirection (f) {
    if (f[m - 2][n - 1] === f[m - 1][n - 2]) return 'both'
    else if (f[m - 2][n - 1] < f[m - 1][n - 2]) return 'up'
    return 'left'
  }
  function bfs (q) {
    const d = Array(m).fill(0).map(() => Array(n).fill(1e10))
    for (const [x, y] of q) d[x][y] = 0
    while (q.length) {
      const [x, y] = q.shift()
      for (const [dx, dy] of [[0, 1], [0, -1], [-1, 0], [1, 0]]) {
        const i = x + dx; const j = y + dy
        if (i >= 0 && i < m && j >= 0 && j < n && g[i][j] !== 2) {
          if (d[i][j] !== 1e10) continue
          d[i][j] = Math.min(d[i][j], d[x][y] + 1)
          q.push([i, j])
        }
      }
    }
    return d
  }
}
