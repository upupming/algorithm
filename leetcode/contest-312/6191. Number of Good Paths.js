/**
 * @param {number[]} vals
 * @param {number[][]} edges
 * @return {number}
 */
const numberOfGoodPaths = function (vals, edges) {
  const n = vals.length
  const fa = Array(n).fill(0).map((_, idx) => idx)
  const sz = Array(n).fill(1)
  const cnts = Array(n).fill(0).map((_, idx) => ({ [vals[idx]]: 1 }))
  edges = edges.map((e, idx) => [...e, Math.max(vals[e[0]], vals[e[1]])]).sort((a, b) => a[2] - b[2])
  const m = edges.length
  let ans = n
  const cnt = {}
  const get = (x) => {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x, y) => {
    let fx = get(x); let fy = get(y)
    if (fx === fy) return
    if (sz[fx] > sz[fy]) [fx, fy] = [fy, fx]
    fa[fx] = fy
    sz[fy] += sz[fx]
    const cx = cnts[fx]; const cy = cnts[fy]
    // 必须要用按秩合并，否则这里的复制次数太多会导致 TLE/MLE
    for (const [k, v] of Object.entries(cx)) {
      cy[k] ??= 0
      cy[k] += v
    }
    // console.log(x, y, cnts[fy])
  }
  for (let i = 0; i < m; i++) {
    let j = i
    const p = new Set(); const t = edges[i][2]
    while (j < m && edges[j][2] === edges[i][2]) {
      merge(edges[j][0], edges[j][1])
      j++
    }
    for (let k = i; k < j; k++) {
      if (vals[edges[k][0]] === t) {
        p.add(get(edges[k][0]))
      }
      if (vals[edges[k][1]] === t) {
        p.add(get(edges[k][1]))
      }
    }
    // console.log(t, p)
    for (const x of p) {
      // console.log(x, t, cnts[x][t])
      const c = cnts[x][t]
      ans += c * (c - 1) / 2
    }

    i = j - 1
  }
  return ans
}
