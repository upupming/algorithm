function minDistance (houses: number[], k: number): number {
  houses.sort((a, b) => a - b)
  const n = houses.length
  const sum = Array<number>(n + 1).fill(0)
  for (let i = 1; i <= n; i++) sum[i] = sum[i - 1] + houses[i - 1]

  // dp[i][j]: 0~i, 使用 j 个邮箱时的最小距离和
  const dp = [...Array(n)].map(() => Array<number>(k + 1).fill(1e10))
  for (let i = 0; i < n; i++) {
    for (let j = 1; j <= k; j++) {
      for (let l = 0; l <= i; l++) {
        // 0~l-1 使用 j-1 个邮箱，l~i 使用 1 个邮箱
        dp[i][j] = Math.min(
          dp[i][j],
          (dp[l - 1]?.[j - 1] ?? 0) + minDist(l, i)
        )
      }
    }
  }
  return dp[n - 1][k]
  // 前缀和优化: O(1)
  function minDist (l: number, r: number): number {
    // sum 数组下标以 1 开始
    l++; r++
    const mid = l + r >> 1
    const leftLen = mid - l + 1; const rightLen = r - mid
    // 用 houses[mid - 1] 是因为 houses 数组下标以 0 开始
    return leftLen * houses[mid - 1] - (sum[mid] - sum[l - 1]) + (sum[r] - sum[mid]) - rightLen * houses[mid - 1]
  }
};
