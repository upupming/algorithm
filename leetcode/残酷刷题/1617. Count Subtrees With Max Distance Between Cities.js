/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[]}
 */
const countSubgraphsForEachDiameter = function (n, edges) {
  const e = Array(n).fill(0).map(() => [])
  for (const [x, y] of edges) e[x - 1].push(y - 1), e[y - 1].push(x - 1)
  const bfs = (st, x) => {
    const d = Array(n).fill(1e10)
    const q = [x]
    d[x] = 0
    let maxID = x
    while (q.length) {
      const cur = q.shift()
      for (const y of e[cur]) {
        if ((st >> y & 1) && d[y] > d[cur] + 1) {
          d[y] = d[cur] + 1
          q.push(y)
          maxID = y
        }
      }
    }
    return {
      maxID,
      d
    }
  }
  const ans = Array(n - 1).fill(0)
  for (let i = 1; i < 1 << n; i++) {
    let m = 0; let x
    for (let j = 0; j < n; j++) {
      if (i >> j & 1) m++, x = j
    }
    const { maxID: s, d } = bfs(i, x)
    let reached = 0
    for (let i = 0; i < n; i++) if (d[i] < 1e10) reached++
    if (reached < m) continue
    const { d: d1 } = bfs(i, s)
    let max = 0
    for (let j = 0; j < n; j++) {
      if (i >> j & 1) {
        max = Math.max(max, d1[j])
      }
    }
    // console.log(i.toString(2), s, d1)
    ans[max - 1]++
  }
  return ans
}
