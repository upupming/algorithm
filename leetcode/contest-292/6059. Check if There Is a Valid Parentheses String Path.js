/**
 * @param {character[][]} grid
 * @return {boolean}
 */
const hasValidPath = function (grid) {
  const m = grid.length; const n = grid[0].length
  grid = grid.map(g => g.map((a) => a === '(' ? 1 : -1))
  if ((m + n) % 2 === 0) return false
  const max = Array(m).fill(0).map(() => Array(n).fill(-1e5))
  const min = Array(m).fill(0).map(() => Array(n).fill(1e5))
  if (grid[0][0] >= 0) min[0][0] = grid[0][0], max[0][0] = grid[0][0]
  // console.log(grid)
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      // 从 [i-1, j] 过来
      if (i >= 1) {
        // tmpMin < 0 但是 tmpMax >= 0 的情况，我们 i, j 仍然合法，min 值为 0
        const tmpMin = min[i - 1][j] + grid[i][j]; const tmpMax = max[i - 1][j] + grid[i][j]
        if (tmpMax >= 0) min[i][j] = Math.min(min[i][j], Math.max(tmpMin, 0))
        if (tmpMax >= 0) max[i][j] = Math.max(max[i][j], tmpMax)
      }
      // 从 [i, j-1] 过来
      if (j >= 1) {
        const tmpMin = min[i][j - 1] + grid[i][j]; const tmpMax = max[i][j - 1] + grid[i][j]
        if (tmpMax >= 0) min[i][j] = Math.min(min[i][j], Math.max(tmpMin, 0))
        if (tmpMax >= 0) max[i][j] = Math.max(max[i][j], tmpMax)
      }
    }
  }
  return min[m - 1][n - 1] === 0 && max[m - 1][n - 1] >= 0
}
