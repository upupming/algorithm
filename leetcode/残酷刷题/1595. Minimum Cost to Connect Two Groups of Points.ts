/**
 * dp[i][j]
 * i 表示左边前 i 个数
 * j 二进制表示右边的匹配状态
 * 如果左边第 i 个数匹配的右边的元素的二进制表示是 j 的话，那么转移：
 * dp[i][j] = min(dp[i][j], dp[i-1][j - subset] + cost[i][subset])
 * 注意最优解第 i 个数选的 subset 一定是和前 i-1 个互斥的
 * 有一种情况是第 i 个数不一定选了新的点，有可能选一个已经匹配过的点
 */
function connectTwoGroups (cost: number[][]): number {
  const [m, n] = [cost.length, cost[0].length]
  const dp = [...Array(m + 1)].map(() => Array<number>(1 << n).fill(1e10))
  const costs = [...Array(m)].map(() => Array<number>(1 << n).fill(0))
  // costs[i][j] 表示左边 i 到右边集合 j 的代价
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < 1 << n; j++) {
      for (let k = 0; k < n; k++) {
        if (j >> k & 1) costs[i][j] += cost[i][k]
      }
    }
  }
  dp[0][0] = 0
  // m * 3^n
  for (let i = 1; i <= m; i++) {
    for (let j = 0; j < 1 << n; j++) {
      // 枚举 j 的所有子集
      for (let subset = j; subset > 0; subset = (subset - 1) & j) {
        dp[i][j] = Math.min(
          dp[i][j],
          dp[i - 1][j - subset] + costs[i - 1][subset]
        )
      }

      // i 选了右边最小的一个点
      for (let k = 0; k < n; k++) {
        dp[i][j] = Math.min(dp[i][j], dp[i - 1][j] + cost[i - 1][k])
      }
    }
  }

  return dp[m][(1 << n) - 1]
};
