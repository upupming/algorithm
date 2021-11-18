function jobScheduling (startTime: number[], endTime: number[], profit: number[]): number {
  const n = startTime.length
  const indices = [...Array(n)].map((_, idx) => idx).sort((i, j) => endTime[i] - endTime[j])
  const f: number[] = []
  // g[i] 表示以 <= i 为结尾的总和最大值
  const g: number[] = []
  let ans = 0
  for (let i = 0; i < n; i++) {
    const idx = indices[i]
    const s = startTime[idx]
    // 找到 <= s 的最后一个位置
    let [l, r] = [0, f.length - 1]
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (endTime[f[mid]] <= s) l = mid
      else r = mid - 1
    }
    const prev = f[l]
    // console.log(l, prev, endTime[prev], s)
    if (l < f.length && endTime[prev] <= s) {
      ans = Math.max(ans, g[prev] + profit[idx])
      f.push(idx); g[idx] = ans
    } else {
      ans = Math.max(ans, profit[idx])
      f.push(idx); g[idx] = ans
    }
    // console.log(i, idx, s, prev, g[prev], profit[idx], g[idx], ans)
  }
  return ans
};
