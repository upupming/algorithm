function canDistribute (nums: number[], quantity: number[]): boolean {
  let cnt = []
  nums.forEach(x => { cnt[x] ??= 0, cnt[x] += 1 })
  cnt = cnt.filter(x => x)
  const n = cnt.length; const m = quantity.length
  const cost = Array(1 << m).fill(0)
  for (let i = 0; i < 1 << m; i++) {
    for (let j = 0; j < m; j++) {
      if (i >> j & 1) cost[i] += quantity[j]
    }
  }
  const dp = [...Array(n)].map(() => Array(1 << m).fill(0))
  for (let j = 0; j < 1 << m; j++) {
    if (cost[j] <= cnt[0]) dp[0][j] = 1
  }
  for (let i = 1; i < n; i++) {
    for (let j = 0; j < 1 << m; j++) {
      for (let k = j; k >= 0; k = (k - 1) & j) {
        const l = j - k
        dp[i][j] = dp[i][j] || (dp[i - 1][k] && cost[l] <= cnt[i])
        if (k == 0 || dp[i][j]) break
      }
    }
  }
  return dp[n - 1][(1 << m) - 1]
};
