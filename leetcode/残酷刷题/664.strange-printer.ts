/*
 * @lc app=leetcode id=664 lang=typescript
 *
 * [664] Strange Printer
 * 区间 DP 问题，打印区间 [i, j] 可以划分成打印 [i, k-1], k, [k+1, j]
 * 枚举所有的可能的划分 k 即可，满足 s[k] == s[i] 的地方
 */

// @lc code=start
function strangePrinter (s: string): number {
  const n = s.length
  const f = Array<number[]>(n).fill([]).map(() => Array<number>(n).fill(1e10))

  for (let len = 1; len <= n; len++) {
    for (let i = 0; i + len - 1 < n; i++) {
      const j = i + len - 1
      if (len === 1) {
        f[i][j] = 1
        continue
      }

      for (let k = i; k <= j; k++) {
        if (s[k] === s[i]) {
          // 特殊情况处理
          if (k === i) f[i][k - 1] = 1
          if (k === j) {
            f[k + 1] ||= []
            f[k + 1][j] = 0
          }
          f[i][j] = Math.min(f[i][j], f[i][k - 1] + f[k + 1][j])
        }
      }
    }
  }

  return f[0][n - 1]
};
// @lc code=end
