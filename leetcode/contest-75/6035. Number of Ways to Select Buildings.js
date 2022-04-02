/**
 * @param {string} s
 * @return {number}
 */
const numberOfWays = function (s) {
  const n = s.length
  const t = s.split('').map(Number)
  let ans = solve(t)
  for (let i = 0; i < n; i++) {
    t[i] = 1 - t[i]
  }
  ans += solve(t)
  return ans

  function solve (t) {
    let c0 = 0; let cx = 0; let ans = 0
    for (let i = 0; i < n; i++) c0 += t[i] === 0
    for (let i = 0; i < n; i++) {
      if (t[i] === 0) cx++
      else {
        const cy = c0 - cx
        ans += cx * cy
      }
    }
    return ans
  }
}
