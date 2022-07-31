/**
 * @param {number[]} edges
 * @param {number} node1
 * @param {number} node2
 * @return {number}
 */
const closestMeetingNode = function (edges, node1, node2) {
  const n = edges.length
  const e = edges.map((x) => {
    if (x === -1) return []
    return [x]
  })
  const dij = (s) => {
    const d = Array(n).fill(1e10)
    d[s] = 0
    const q = [s]; const v = {}
    while (q.length) {
      const now = q.shift()
      if (v[now]) continue
      v[now] = 1
      for (const y of e[now]) {
        d[y] = Math.min(d[now] + 1, d[y])
        q.push(y)
      }
    }
    return d
  }
  const d1 = dij(node1)
  const d2 = dij(node2)
  // console.log(d1, d2)
  let ans = 1e10; let idx = -1
  for (let i = 0; i < n; i++) {
    const t = Math.max(d1[i], d2[i])
    if (ans > t) {
      ans = t
      idx = i
    }
  }
  return ans === 1e10 ? -1 : idx
}
