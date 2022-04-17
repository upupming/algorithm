/**
 * @param {number[]} parent
 * @param {string} s
 * @return {number}
 */
const longestPath = function (p, s) {
  const n = p.length
  const e = Array(n).fill(0).map(() => [])
  for (let i = 1; i < n; i++) {
    e[p[i]].push(i)
    e[i].push(p[i])
  }
  let a = 1
  const dfs = (x, fa) => {
    const ans = []
    // console.log(x, path)
    for (const y of e[x]) {
      if (y === fa) continue
      const tmp = dfs(y, x)
      ans.push(tmp)
    }
    ans.sort((a, b) => b - a)
    const tmp = (ans[0] ?? 0) + (ans[1] ?? 0) + 1
    a = Math.max(a, tmp)
    return (s[fa] === s[x]) ? 0 : ((ans[0] ?? 0) + 1)
  }

  dfs(0, -1, s[0])
  return a
}
