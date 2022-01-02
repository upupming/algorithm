function maximumInvitations (favorite: number[]): number {
  const n = favorite.length
  // 原图
  const f = [...Array(n)].map((): number[] => [])
  // 反图
  const g = [...Array(n)].map((): number[] => [])
  const deg = Array<number>(n).fill(0)
  favorite.forEach((y, x) => {
    f[x].push(y)
    g[y].push(x)
    deg[y]++
  })

  // 拓扑排序，剪掉原图上的所有树枝，结束之后树枝的入度都变成 0
  const q: number[] = [...Array(n)].map((_, idx) => idx).filter(i => deg[i] === 0)
  while (q.length) {
    const x = q.pop()!
    for (const y of f[x]) {
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }

  // 多个基环大小等于 2 的基环树，每个基环树所对应的链，都可以拼在其余链的末尾。可以将这些链全部拼成一个圆桌，其大小记作 sumListSize。
  let sumListSize = 0
  // 对于基环大小大于 2 的情况，圆桌的最大员工数目即为最大的基环大小，记作 maxCycleSize。
  let maxCycleSize = 0

  const v = Array<boolean>(n).fill(false)
  // 遍历基环
  const dfs = (x: number, nodes: number[]) => {
    if (v[x]) return
    v[x] = true
    nodes.push(x)
    for (const y of f[x]) dfs(y, nodes)
  }
  // 在反向图上遍历，寻找最大的链
  const rdfs = (x: number, fa: number) => {
    let ans = 0
    for (const y of g[x]) {
      if (y === fa) continue
      ans = Math.max(rdfs(y, x), ans)
    }
    return ans + 1
  }

  for (let i = 0; i < n; i++) {
    // 基环上的点
    if (deg[i] > 0) {
      const nodes: number[] = []
      dfs(i, nodes)
      // console.log(i, nodes)
      // 基环大小为 2
      if (nodes.length === 2) {
        const [x, y] = nodes
        const m1 = rdfs(x, y); const m2 = rdfs(y, x)
        // console.log(x, y, m1, m2)
        sumListSize += m1 + m2
      } else {
        maxCycleSize = Math.max(maxCycleSize, nodes.length)
      }
    }
  }

  // 要么是所有的基环大小为 2 的链串起来；要么是最大的大小大于 2 的基环
  return Math.max(sumListSize, maxCycleSize)
};
