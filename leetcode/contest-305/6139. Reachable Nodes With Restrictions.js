/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} restricted
 * @return {number}
 */
 var reachableNodes = function(n, edges, restricted) {
  const e = Array(n).fill(0).map(() => [])
  const r = new Set(restricted)
  for (const [x, y] of edges) {
      e[x].push(y)
      e[y].push(x)
  }
  const v = {}
  const t = new Set()
  const dfs = (x, fa) => {
      if (v[x]) return
      v[x] = 1
      t.add(x)
      for (const y of e[x]) {
          if (y === fa) continue
          if (!r.has(y)) dfs(y, x)
      }
  }
  dfs(0, -1)
  return t.size
};
