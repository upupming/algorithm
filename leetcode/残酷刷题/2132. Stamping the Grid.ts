function possibleToStamp (grid: number[][], stampHeight: number, stampWidth: number): boolean {
  const n = grid.length; const m = grid[0].length
  const f: number[][] = [...Array(n + 1)].map(() => Array(m + 1).fill(0))
  const g: number[][] = [...Array(n + 1)].map(() => Array(m + 1).fill(0))
  const gSum: number[][] = [...Array(n + 1)].map(() => Array(m + 1).fill(0))
  for (let i = 1; i <= n; i++) {
    for (let j = 1; j <= m; j++) {
      f[i][j] = grid[i - 1][j - 1] + f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1]
    }
  }
  for (let i = 1; i <= n; i++) {
    for (let j = 1; j <= m; j++) {
      const i1 = i + stampHeight - 1; const j1 = j + stampWidth - 1
      if (i1 > n || j1 > m) continue
      const s = f[i1][j1] - f[i1][j - 1] - f[i - 1][j1] + f[i - 1][j - 1]
      // 这个区间内没有任何occupied，i, j 处可以放置邮票
      if (s === 0) {
        // console.log(i, j)
        g[i][j] = 1
      }
    }
  }

  for (let i = 1; i <= n; i++) {
    for (let j = 1; j <= m; j++) {
      gSum[i][j] = g[i][j] + gSum[i - 1][j] + gSum[i][j - 1] - gSum[i - 1][j - 1]
      if (grid[i - 1][j - 1] === 1) continue
      const i0 = Math.max(0, i - stampHeight); const j0 = Math.max(0, j - stampWidth)
      const section = gSum[i][j] - gSum[i][j0] - gSum[i0][j] + gSum[i0][j0]
      // console.log(i, j, section)
      if (section === 0) {
        return false
      }
    }
  }
  return true
};
