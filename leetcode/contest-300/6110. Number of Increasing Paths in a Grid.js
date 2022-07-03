/**
 * @param {number[][]} grid
 * @return {number}
 */
const countPaths = function (g) {
  const dx = [0, 0, 1, -1]; const dy = [1, -1, 0, 0]
  const m = g.length; const n = g[0].length
  const mp = {}; const P = 1e9 + 7
  const dfs = (i, j) => {
    if (mp[`${i}_${j}`] != null) return mp[`${i}_${j}`]
    let ans = 1
    for (let k = 0; k < 4; k++) {
      const x = i + dx[k]; const y = j + dy[k]
      if (x >= 0 && x < m && y >= 0 && y < n && g[i][j] < g[x][y]) ans = (ans + dfs(x, y)) % P
    }
    return mp[`${i}_${j}`] = ans
  }
  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      ans = (ans + dfs(i, j)) % P
    }
  }
  return ans
}
