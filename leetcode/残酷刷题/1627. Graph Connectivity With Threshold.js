/**
 * @param {number} n
 * @param {number} threshold
 * @param {number[][]} queries
 * @return {boolean[]}
 */
const areConnected = function (n, threshold, queries) {
  const fa = [...Array(n + 1)].map((_, idx) => idx)
  const get = (x) => {
    if (fa[x] === x) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x, y) => {
    const fx = get(x); const fy = get(y)
    fa[fx] = fy
  }
  for (let i = threshold + 1; i <= n; i++) {
    for (let j = i; j <= n; j += i) {
      merge(i, j)
    }
  }
  return queries.map(q => get(q[0]) === get(q[1]))
}
