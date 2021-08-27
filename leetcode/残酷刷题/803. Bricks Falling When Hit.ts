function hitBricks (grid: number[][], hits: number[][]): number[] {
  const [m, n] = [grid.length, grid[0].length]
  for (const h of hits) {
    grid[h[0]][h[1]] += 2
  }
  const valid = (i: number, j: number) => i >= 0 && i < m && j >= 0 && j < n
  const idx = (i: number, j: number) => i * n + j + 1
  const fa = [...Array(m * n + 1)].map((_, idx) => idx)
  const sz = [...Array<number>(m * n + 1)].fill(1)
  const find = (x: number): number => {
    if (x === fa[x]) return x
    return fa[x] = find(fa[x])
  }
  const merge = (x: number, y: number) => {
    let [fx, fy] = [find(x), find(y)]
    if (fx === fy) return
    // 如果有一方是 0 （超级节点），不妨设 fx 为 0
    if (fy === 0) [fx, fy] = [fy, fx]
    // console.log(x, y, fx, fy)
    fa[fy] = fx
    sz[fx] += sz[fy]
  }
  const [dx, dy] = [[0, 0, 1, -1], [1, -1, 0, 0]]
  for (let j = 0; j < n; j++) {
    if (grid[0][j] === 1) merge(0, idx(0, j))
  }
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (grid[i][j] !== 1) continue
      for (let k = 0; k < 4; k++) {
        const [x, y] = [i + dx[k], j + dy[k]]
        if (valid(x, y) && grid[x][y] === 1) {
          merge(idx(i, j), idx(x, y))
        }
      }
    }
  }
  const ans = []
  for (let i = hits.length - 1; i >= 0; i--) {
    const [a, b] = hits[i]
    if (grid[a][b] === 2) { ans.push(0); continue }
    grid[a][b] = 1

    const s1 = sz[0]
    if (a === 0) merge(0, idx(a, b))
    for (let k = 0; k < 4; k++) {
      const [x, y] = [a + dx[k], b + dy[k]]
      if (valid(x, y) && grid[x][y] === 1) {
        merge(idx(a, b), idx(x, y))
      }
    }
    const s2 = sz[0]
    // console.log('s', a, b, s1, s2)
    ans.push(s2 > s1 ? s2 - s1 - 1 : 0)
  }
  return ans.reverse()
};
