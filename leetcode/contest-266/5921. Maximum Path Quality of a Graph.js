/**
 * @param {number[]} values
 * @param {number[][]} edges
 * @param {number} maxTime
 * @return {number}
 */
const maximalPathQuality = function (values, edges, maxTime) {
  const n = values.length
  const e = [...Array(n)].map(() => [])
  for (const [u, v, time] of edges) {
    e[u].push([v, time])
    e[v].push([u, time])
  }
  let ans = 0
  const s = new Set([0])
  const dfs = (u, t, w) => {
    if (t > maxTime) return
    if (u === 0) {
      // console.log(t, s, w)
      ans = Math.max(ans, w)
    }
    for (const [y, time] of e[u]) {
      let added = false
      if (!s.has(y)) {
        w += values[y]
        s.add(y)
        added = true
      }
      dfs(y, t + time, w)
      if (added) {
        s.delete(y)
        w -= values[y]
      }
    }
  }
  dfs(0, 0, values[0])
  return ans
}
