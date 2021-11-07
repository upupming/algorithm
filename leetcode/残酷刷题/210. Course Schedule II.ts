function findOrder (n: number, p: number[][]): number[] {
  const e = [...Array(n)].map(() => []); const deg = Array(n).fill(0)
  const ans = []; const q = []
  for (const [a, b] of p) {
    e[b].push(a)
    deg[a]++
  }
  for (let i = 0; i < n; i++) if (deg[i] === 0) q.push(i)
  while (q.length) {
    const x = q.shift()
    ans.push(x)
    for (const y of e[x]) {
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }
  return ans.length === n ? ans : []
};
