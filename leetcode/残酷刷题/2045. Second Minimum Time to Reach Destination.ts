function secondMinimum (n: number, edges: number[][], time: number, change: number): number {
  const adj: number[][] = []
  edges.forEach(e => {
    adj[e[0]] ??= []; adj[e[0]].push(e[1])
    adj[e[1]] ??= []; adj[e[1]].push(e[0])
  })
  const q: number[][] = []
  const v = Array<number>(n + 1).fill(0)
  const dist = Array<number>(n + 1).fill(-1)
  q.push([1, 0]); dist[1] = 0
  while (q.length) {
    const [cur, t] = q.shift()!

    let tt
    const round = Math.floor(t / change)
    if (round % 2 === 0) tt = t + time
    else tt = (round + 1) * change + time

    for (const y of adj[cur]) {
      // tt 比之前的距离要大，就更新，因此保证求第 2 大的值
      if (v[y] < 2 && dist[y] < tt) {
        dist[y] = tt
        v[y] += 1
        q.push([y, tt])

        if (v[y] === 2 && y === n) return tt
      }
    }
  }
  return -1
};
