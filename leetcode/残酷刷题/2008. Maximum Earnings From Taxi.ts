function maxTaxiEarnings (n: number, rides: number[][]): number {
  const f = Array<number>(n + 1).fill(0)
  const g = Array<number>(n + 1).fill(0)
  rides.sort((a, b) => a[1] - b[1])
  const m = rides.length
  for (let i = 1, j = 0; i <= n; i++) {
    // 处理所有结束时间为 i 的
    while (j < m && rides[j][1] === i) {
      const r = rides[j]
      f[i] = Math.max(f[i], g[r[0]] + r[1] - r[0] + r[2])
      j++
    }
    g[i] = Math.max(g[i - 1], f[i])
    console.log(i, f[i], g[i])
  }
  return g[n]
};
