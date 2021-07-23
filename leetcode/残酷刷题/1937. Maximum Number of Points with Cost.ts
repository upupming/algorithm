function maxPoints (points: number[][]): number {
  const [m, n] = [points.length, points[0].length]
  const f = [...Array(2)].map(() => Array<number>(n))
  const g = [...Array(2)].map(() => Array<number>(n))
  const tmp = Array<number>(n).fill(0)
  for (let i = 0; i < n; i++) {
    f[0][i] = Math.max(f[0][i - 1] ?? -1e10, points[0][i] - i)
  }
  for (let i = n - 1; i >= 0; i--) {
    g[0][i] = Math.max(g[0][i + 1] ?? -1e10, points[0][i] + i)
  }
  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      tmp[j] = Math.max(f[0][j] + points[i][j] + j, g[0][j] + points[i][j] - i)
      ans = Math.max(ans, tmp[j])
      f[1][j] = Math.max(f[1][j - 1] ?? -1e10, tmp[j] - j)
    }
    for (let j = n - 1; j >= 0; j--) {
      g[1][j] = Math.max(g[1][j + 1] ?? -1e10, tmp[j] + j)
    }
    for (let j = 0; j < n; j++) {
      f[0][j] = f[1][j]
    }
  }
  return ans
};
