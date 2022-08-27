/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[]}
 */
const sumOfDistancesInTree = function (n, edges) {
  const e = Array(n).fill(0).map(() => [])
  for (const [x, y] of edges) {
    e[x].push(y)
    e[y].push(x)
  }
  const dist = Array(n).fill(1e10)
  const ans = []
  // 求每个节点到 0 的距离
  const dfs = (cur = 0, prev = -1, d = 0) => {
    dist[cur] = d
    for (const next of e[cur]) {
      if (next === prev) continue
      dfs(next, cur, d + 1)
    }
  }
  dfs()
  ans[0] = 0
  for (let i = 0; i < n; i++) ans[0] += dist[i]

  const sz = Array(n).fill(0)
  // 求每个节点的子树大小
  const dfs1 = (cur = 0, prev = -1) => {
    let ans = 1
    for (const next of e[cur]) {
      if (next === prev) continue
      ans += dfs1(next, cur)
    }
    return sz[cur] = ans
  }
  dfs1()

  // 对每个节点进行 re-root
  const dfs2 = (cur = 0, prev = -1) => {
    if (prev !== -1) {
      const a = sz[cur]
      const b = n - a
      ans[cur] = ans[prev] - a + b
    }
    for (const next of e[cur]) {
      if (next === prev) continue
      dfs2(next, cur)
    }
  }
  dfs2()

  return ans
}
