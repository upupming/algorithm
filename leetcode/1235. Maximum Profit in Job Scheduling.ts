function jobScheduling (startTime: number[], endTime: number[], profit: number[]): number {
  const n = startTime.length
  const idx = [...Array(n)].map((_, i) => i)
  idx.sort((a, b) => endTime[a] - endTime[b])
  const max = endTime.reduce((p, c) => Math.max(p, c), 0)
  const f = Array<number>(max + 1).fill(0)
  const g = Array<number>(max + 1).fill(0)
  for (let i = 1, j = 0; i <= max; i++) {
    while (endTime[idx[j]] === i) {
      f[i] = Math.max(f[i], g[startTime[idx[j]]] + profit[idx[j]])
      j++
    }
    g[i] = Math.max(g[i - 1], f[i])
  }
  return g[max]
};
