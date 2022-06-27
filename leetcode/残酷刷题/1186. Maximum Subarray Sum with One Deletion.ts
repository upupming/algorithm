function maximumSum (arr: number[]): number {
  const n = arr.length
  // f[i][0]: not use deletion, f[i][1]: has used deletion
  const f: number[][] = Array(n + 1).fill(0).map(() => [])
  f[0][0] = f[0][1] = 0
  let ans = -1e10
  for (let i = 1; i <= n; i++) {
    f[i][0] = Math.max(f[i - 1][0], 0) + arr[i - 1]
    f[i][1] = Math.max(f[i - 1][1], f[i - 2]?.[0] ?? 0, 0) + arr[i - 1]
    ans = Math.max(ans, f[i][0], f[i][1])
  }
  return ans
};
