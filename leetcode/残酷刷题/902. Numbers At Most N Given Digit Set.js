/**
 * @param {string[]} digits
 * @param {number} n
 * @return {number}
 */
const atMostNGivenDigitSet = function (d, n) {
  const t = d.length
  const s = String(n)
  const m = s.length
  let ans = 0
  // 长度小于 m 的情况
  for (let i = 1; i < m; i++) {
    ans += Math.pow(t, i)
  }
  // 长度等于 m 的情况
  const dfs = (path = []) => {
    // 刚好等于 s
    if (path.length === m) {
      return 1
    }
    let ans = 0
    for (const i of d) {
      if (i > s[path.length]) break
      // 填上之后，已经小于，后面的可以随便填了
      if (i < s[path.length]) {
        ans += Math.pow(t, m - path.length - 1)
      } else {
        path.push(i)
        ans += dfs(path)
        path.pop()
      }
    }
    // console.log(path, ans)
    return ans
  }
  return ans + dfs()
}
