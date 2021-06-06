/*
动态规划
f[i][j] 表示走完前 i 条路，skip 了 j 次的所需时间
答案就是 f[n][j] <= hoursBefore 时最小的 j
状态转移:
第 i 条路 skip: f[i-1][j-1] + d[i]/speed
第 i 条路不 skip: f[i-1][j] + ceil(d[i]/speed)
*/
function minSkips (dist: number[], speed: number, hoursBefore: number): number {
  const n = dist.length
  const f = Array<number[]>(n + 1).fill([]).map(() => Array<number>(n + 1).fill(1e10))
  f[0][0] = 0
  for (let i = 1; i <= n; i++) {
    for (let j = 0; j <= i; j++) {
      if (j - 1 >= 0) {
        f[i][j] = f[i - 1][j - 1] + dist[i - 1] / speed
      }
      if (i - 1 >= j) {
        f[i][j] = Math.min(
          f[i][j],
          Math.ceil(f[i - 1][j] + dist[i - 1] / speed - 1e-8)
        )
      }
    }
  }
  for (let j = 0; j <= n; j++) {
    if (f[n][j] <= hoursBefore + 1e-8) return j
  }
  return -1
};
