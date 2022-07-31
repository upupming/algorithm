/**
 * @param {number[]} edges
 * @return {number}
 环套树（也称基环外向树）找环模板题。只要一张图边数不超过点数就是环套数。
 环套树的特性就是每个连通块最多只有一个环，把这个环去掉以后，剩下的部分是若干树。
 https://leetcode.cn/circle/discuss/uPC575/view/MXTAjy/
 */
const longestCycle = function (edges) {
  const n = edges.length
  const e = edges.map((x, idx) => {
    if (x === -1) return []
    return [x]
  })

  const f = {}; const d = Array(n).fill(1e10)
  let ans = -1
  const bfs = (s) => {
    d[s] = 0, f[s] = s
    const q = [s]
    while (q.length) {
      const x = q.shift()
      for (const y of e[x]) {
        // 第二次访问
        if (f[y] === s) {
          ans = Math.max(ans, d[x] + 1 - d[y])
        } else {
          if (d[y] > d[x] + 1) {
            d[y] = d[x] + 1
            f[y] = s
            q.push(y)
          }
        }
      }
    }
  }
  for (let i = 0; i < n; i++) {
    if (d[i] === 1e10) bfs(i)
  }
  return ans
}
