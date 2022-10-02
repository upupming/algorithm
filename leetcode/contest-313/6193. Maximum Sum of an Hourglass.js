/**
 * @param {number[][]} grid
 * @return {number}
 */
const maxSum = function (g) {
  const m = g.length; const n = g[0].length
  let ans = 0
  for (let i = 0; i + 2 < m; i++) {
    for (let j = 0; j + 2 < n; j++) {
      let t = 0
      for (let l = i; l <= i + 2; l++) {
        for (let s = j; s <= j + 2; s++) {
          t += g[l][s]
        }
      }
      t -= g[i + 1][j] + g[i + 1][j + 2]

      ans = Math.max(ans, t)
    }
  }
  return ans
}
