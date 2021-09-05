function minSessions (tasks: number[], sessionTime: number): number {
  const n = tasks.length
  const f = Array<number>(1 << n).fill(20)
  const idx = [...Array<number>(n)].map((_, idx) => idx)
  f[0] = 0
  for (let i = 1; i < 1 << n; i++) {
    const sum = idx.reduce((acc, k) => acc + ((i >> k & 1) ? tasks[k] : 0), 0)
    if (sum <= sessionTime) { f[i] = 1; continue }
    for (let j = i; j; j = (j - 1) & i) f[i] = Math.min(f[i], f[j] + f[i - j])
  }
  return f.pop()!
};
