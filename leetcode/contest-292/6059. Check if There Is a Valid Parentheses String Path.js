/**
 * @param {character[][]} grid
 * @return {boolean}
 */
const hasValidPath = function (grid) {
  const m = grid.length; const n = grid[0].length
  const dp = Array(m).fill(0).map(() => Array(n).fill(0).map(() => new Set()))

  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (i === 0 && j === 0) {
        if (grid[0][0] === '(') dp[0][0].add(1)
        continue
      }

      const s = new Set()
      if (i - 1 >= 0) [...dp[i - 1][j]].forEach(x => s.add(x))
      if (j - 1 >= 0) [...dp[i][j - 1]].forEach(x => s.add(x))

      for (const c of s) {
        const x = c + (grid[i][j] === '(' ? 1 : -1)
        if (x >= 0) dp[i][j].add(x)
        // console.log(i, j, dp[i][j])
      }
    }
  }
  return dp[m - 1][n - 1].has(0)
}
