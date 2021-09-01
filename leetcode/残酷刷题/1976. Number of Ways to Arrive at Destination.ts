function countPaths (n: number, roads: number[][]): number {
  const edge: Array<Array<[number, number]>> = [...Array(n)].map(() => [])
  const P = 1e9 + 7
  for (const [x, y, time] of roads) {
    edge[x].push([y, time])
    edge[y].push([x, time])
  }
  const q: number[] = []
  const d = Array<number>(n).fill(1e12)
  const v = Array<boolean>(n).fill(false)
  // cnt[x][y] 表示从 0->...->x->y 的最短路径数
  const cnt = [...Array(n)].map(() => Array<number>(n).fill(0))
  const relax = (x: number, y: number) => {
    cnt[y][x] = 0
    for (const m of cnt[x]) {
      cnt[y][x] = (cnt[y][x] + m) % P
    }
  }
  d[0] = 0; v[0] = true; cnt[0][0] = 1
  q.push(0)
  while (q.length) {
    const x = q.shift()!
    v[x] = false
    for (const [y, time] of edge[x]) {
      if (d[y] > d[x] + time) {
        relax(x, y)
        // 从其他节点进入 y 的都置为 0，因为只有 x->y 这条最短
        for (let i = 0; i < n; i++) {
          if (i !== x) cnt[y][i] = 0
        }
        d[y] = d[x] + time
        if (!v[y]) q.push(y); v[y] = true
      } else if (d[y] === d[x] + time) {
        // === 的时候，要更新 cnt，所以进入判断
        relax(x, y)
        if (!v[y]) q.push(y); v[y] = true
      }
    }
  }
  let ans = 0
  for (let i = 0; i < n; i++)
  { ans = (ans + cnt[n - 1][i]) % P }
  return ans
};
