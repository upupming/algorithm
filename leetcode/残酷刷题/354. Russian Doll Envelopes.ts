function maxEnvelopes (envelopes: number[][]): number {
  const cmp = (a: number[], b: number[]) => {
    if (a[0] === b[0]) return -(a[1] - b[1])
    return a[0] - b[0]
  }
  envelopes.sort(cmp)
  return LIS()
  function LIS () {
    const p: number[][] = []
    for (const e of envelopes) {
      let [l, r] = [0, p.length]
      while (l < r) {
        const mid = l + r >> 1
        if (mid === p.length || (p[mid][1] >= e[1])) r = mid
        else l = mid + 1
      }
      p[l] = e
    }
    return p.length
  }
};
