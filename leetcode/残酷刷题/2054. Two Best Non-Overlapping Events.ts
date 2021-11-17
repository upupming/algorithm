function maxTwoEvents (events: number[][]): number {
  const n = events.length
  const e = events.map((x) => [x[0] - 1, ...x.slice(1)]).sort((a, b) => a[1] - b[1])
  const f = []
  const max = [0]
  let ans = 0
  for (let i = 0; i < n; i++) {
    const x = e[i]
    // 在 f 中找最后一个 <= x[0] 的结束点
    let [l, r] = [0, f.length - 1]
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (f[mid] <= x[0]) l = mid
      else r = mid - 1
    }
    if (l < f.length && f[l] <= x[0]) {
      ans = Math.max(ans, max[l + 1] + x[2])
    } else {
      ans = Math.max(ans, x[2])
    }
    f.push(x[1]), max.push(Math.max(max[max.length - 1], x[2]))
  }
  return ans
};
