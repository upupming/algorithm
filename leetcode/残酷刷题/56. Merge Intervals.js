function merge(intervals: number[][]): number[][] {
  const a = []
  for (const [s, e] of intervals) {
      a.push([s, 1], [e, -1])
  }
  a.sort((x, y) => {
      if (x[0] === y[0]) {
          return -(x[1] - y[1])
      }
      return x[0]-y[0]
  })
  let cnt = 0, ans = [], tmp = []
  for (const t of a) {
      cnt += t[1]
      if (t[1] === 1 && cnt === 1) {
          tmp.push(t[0])
      } else if (cnt === 0) {
          tmp.push(t[0])
          ans.push(tmp)
          tmp = []
      }
  }
  return ans
};
