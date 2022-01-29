/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[]}
 */
const findMinHeightTrees = function (n, edges) {
  // 拓扑排序之后，选择最后的节点作为 MHT root，这样得到的一定是最小高度树
  // 反证法，选择其他的一定不会更优
  const deg = Array(n).fill(0)
  const e = [...Array(n)].map(() => [])
  for (const [a, b] of edges) {
    deg[a]++
    deg[b]++
    e[a].push(b)
    e[b].push(a)
  }
  const q = []
  const h = []
  for (let i = 0; i < n; i++) if (deg[i] === 1 || deg[i] === 0) q.push([i, 0])
  while (q.length) {
    const [x, s] = q.shift()
    // console.log(x, s)
    h[x] = s
    for (const y of e[x]) {
      if (--deg[y] === 1 && h[y] == null) {
        q.push([y, s + 1])
      }
    }
  }
  const ans = []
  const max = h.reduce((p, c) => Math.max(p, c), 0)
  for (let i = 0; i < n; i++) if (h[i] === max) ans.push(i)
  return ans
}
