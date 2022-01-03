function maxEnvelopes (envelopes: number[][]): number {
  const p: number[] = []
  envelopes.sort((a, b) => {
    // 保证 (1, 7), (1, 6) 这种不合法，7, 6 不递增
    if (a[0] === b[0]) return -(a[1] - b[1])
    return a[0] - b[0]
  }).map(x => x[1]).forEach(x => {
    let [l, r] = [0, p.length]
    while (l < r) {
      const mid = l + r >> 1
      if (mid === p.length || p[mid] >= x) r = mid
      else l = mid + 1
    }
    p[l] = x
  })
  return p.length
};
