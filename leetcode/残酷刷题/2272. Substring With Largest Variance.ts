function largestVariance (s: string): number {
  const n = s.length
  // 以 i 结尾的子数组的最大和
  const f: number[] = Array(n + 1).fill(0)
  // 以 i 结尾的并且一定包含 -1 的子数组的最大和
  const g: number[] = Array(n + 1).fill(0)
  let ans = 0
  for (let i = 0; i < 26; i++) {
    for (let j = 0; j < 26; j++) {
      if (j === i) continue

      f[0] = 0
      g[0] = -1e10
      for (let k = 1; k <= n; k++) {
        const ch = s.charCodeAt(k - 1) - 'a'.charCodeAt(0)
        if (ch === i) {
          f[k] = Math.max(f[k - 1], 0) + 1
          g[k] = g[k - 1] + 1
        }
        else if (ch === j) {
          f[k] = Math.max(f[k - 1], 0) - 1
          g[k] = Math.max(g[k - 1], f[k - 1], 0) - 1
        }
        else {
          f[k] = f[k - 1]
          g[k] = g[k - 1]
        }

        ans = Math.max(ans, g[k])
      }
    }
  }
  return ans
};
