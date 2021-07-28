function splitPainting (segments: number[][]): number[][] {
  let [l, r] = [1e6, 0]
  for (const [x, y] of segments) {
    l = Math.min(l, x)
    r = Math.max(r, y)
  }
  const diff = Array<number>(r + 1).fill(0)
  const p = []
  for (const [x, y, c] of segments) {
    diff[x] += c
    diff[y] -= c
    p.push(x)
    p.push(y)
  }
  p.sort((a, b) => a - b)
  let j = 0
  let cur = 0
  let last = l
  const ans = []
  for (let i = l; i <= r; i++) {
    while (j < p.length && p[j] < i) j++
    if (j < p.length && p[j] === i && i !== last) {
      j++
      if (cur !== 0)
      { ans.push([last, i, cur]) }
      last = i
    }
    cur += diff[i]
  }
  return ans
};
