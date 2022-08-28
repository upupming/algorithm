/**
 * @param {number} k
 * @param {number[][]} rowConditions
 * @param {number[][]} colConditions
 * @return {number[][]}
 */
const buildMatrix = function (k, rc, cc) {
  const n = rc.length; const m = cc.length

  const get = (rc) => {
    const e = Array(k + 1).fill(0).map(() => [])
    const deg = Array(k + 1).fill(0)
    for (const [a, b] of rc) {
      e[a].push(b)
      deg[b]++
    }
    const q = []
    for (let i = 1; i <= k; i++) {
      if (deg[i] === 0) q.push(i)
    }
    const r = []
    while (q.length) {
      const x = q.shift()
      r.push(x)
      for (const y of e[x]) {
        if (--deg[y] === 0) {
          q.push(y)
        }
      }
    }
    return r.length === k ? r : false
  }

  const r = get(rc)
  if (!r) return []

  const c = get(cc)
  if (!c) return []

  const ans = Array(k).fill(0).map(() => Array(k).fill(0))
  for (let i = 0; i < k; i++) {
    for (let j = 0; j < k; j++) {
      if (r[i] === c[j]) {
        ans[i][j] = r[i]
      }
    }
  }
  return ans
}
