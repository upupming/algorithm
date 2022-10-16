/**
 * @param {number} n
 * @param {number[][]} edgeList
 * @param {number[][]} queries
 * @return {boolean[]}
 */
const distanceLimitedPathsExist = function (n, edgeList, queries) {
  const fa = Array(n).fill(0).map((_, idx) => idx)
  edgeList.sort((a, b) => a[2] - b[2])
  const ans = []; let i = 0; const m = edgeList.length
  const get = (x) => {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x, y) => {
    const [fx, fy] = [get(x), get(y)]
    fa[fx] = fy
  }
  queries.map((q, idx) => [...q, idx]).sort((a, b) => a[2] - b[2])
    .forEach(([x, y, d, idx]) => {
      while (i < m && edgeList[i][2] < d) {
        merge(edgeList[i][0], edgeList[i][1])
        i++
      }
      ans[idx] = get(x) === get(y)
    })
  return ans
}
