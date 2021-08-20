function maxSumAfterPartitioning (arr: number[], k: number): number {
  const n = arr.length
  const dp = [...Array(n)].map(() => Array<number>(k + 1).fill(0))
  const f = Array<number>(n).fill(0)
  for (let i = 0; i < n; i++) {
    let max = 0
    for (let j = 0; j <= k && j <= i + 1; j++) {
      if (j > 0)
      { max = Math.max(max, arr[i - j + 1]) }
      dp[i][j] = Math.max(dp[i][j], (j > i ? 0 : f[i - j]) + j * max)
      f[i] = Math.max(f[i], dp[i][j])
    }
  }
  return f[n - 1]
};
