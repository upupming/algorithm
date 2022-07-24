/**
 * @param {number[][]} grid
 * @return {number}
 */
const equalPairs = function (g) {
  const n = g.length
  let ans = 0
  for (let r = 0; r < n; r++) {
    for (let c = 0; c < n; c++) {
      let ok = true
      for (let i = 0; i < n; i++) {
        if (g[r][i] != g[i][c]) {
          ok = false
          break
        }
      }
      ans += ok
    }
  }
  return ans
}
