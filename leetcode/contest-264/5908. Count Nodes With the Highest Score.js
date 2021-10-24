/**
 * @param {number[]} parents
 * @return {number}
 */
const countHighestScoreNodes = function (p) {
  const n = p.length
  const sz = Array(n).fill(0)
  const e = [...Array(n)].map(() => [])
  const val = Array(n).fill(1)
  p.forEach((v, idx) => {
    if (v === -1) return
    e[v].push(idx)
  })
  dfs(0, -1)
  let max = 0
  for (let i = 0; i < n; i++) {
    let pSize = n - 1
    for (const ch of e[i]) {
      pSize -= sz[ch]
      if (sz[ch] >= 1) val[i] *= sz[ch]
    }
    if (pSize >= 1) val[i] *= pSize
    max = Math.max(max, val[i])
  }
  // console.log(sz, val)
  let ans = 0
  val.forEach(v => {
    if (v === max) ans++
  })
  return ans
  function dfs (cur, fa) {
    for (const ch of e[cur]) {
      if (ch === fa) continue
      sz[cur] += dfs(ch, cur)
    }
    sz[cur] += 1
    return sz[cur]
  }
}
