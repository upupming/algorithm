/*
 * @lc app=leetcode id=1872 lang=typescript
 *
 * [1872] Stone Game VIII
 * 每个人的目的都是最大化自己的分数，可以直接使用 dp 来做
 * f[i] 表示从 i 开始（1~i 已经被之前的操作合并了），自己做最优选择，最坏情况下的分数，f[i] = max(sum(stones[1~j]) - f[j])
 * 时间复杂度为 O(n^2)，可以进一步优化成 O(n) 的
 */

// @lc code=start
function stoneGameVIII (stones: number[]): number {
  const n = stones.length
  const [sum, f] = [Array<number>(n + 1).fill(0), Array<number>(n + 1).fill(-1e10)]
  for (let i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + stones[i - 1]
  }
  const naive = (stones: number[]): number => {
    f[n] = 0
    for (let i = n; i >= 1; i--) {
      for (let j = i + 1; j <= n; j++) {
        f[i] = Math.max(f[i], sum[j] - f[j])
      }
    }
    return f[1]
  }
  const optimized = (stones: number[]): number => {
    const g = Array<number>(n + 1).fill(-1e10)
    f[n] = 0
    g[n] = sum[n] - 0
    for (let i = n - 1; i >= 1; i--) {
      f[i] = g[i + 1]
      g[i] = Math.max(g[i + 1], sum[i] - f[i])
    }
    return f[1]
  }
  return optimized(stones)
};
// @lc code=end
