/**
 * @param {number} n
 * @param {number[][]} relations
 * @param {number[]} time
 * @return {number}
 */
const minimumTime = function (n, r, t) {
  const deg = Array(n + 1).fill(0)
  const e = Array(n + 1).fill(0).map(() => [])
  const dp = Array(n + 1).fill(0)
  const pre = Array(n + 1).fill(0).map(() => [])
  for (const p of r) {
    deg[p[1]]++
    e[p[0]].push(p[1])
  }

  const q = []
  for (let i = 1; i <= n; i++) {
    if (deg[i] === 0) q.push(i)
  }
  let ans = 0
  while (q.length) {
    const x = q.shift()
    pre[x].forEach(p => {
      // console.log(p, dp[p])
      dp[x] = Math.max(dp[x], dp[p])
    })
    dp[x] += t[x - 1]
    // console.log(x, pre[x], dp[x])
    ans = Math.max(ans, dp[x])
    for (const y of e[x]) {
      pre[y].push(x)
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }
  return ans
}
