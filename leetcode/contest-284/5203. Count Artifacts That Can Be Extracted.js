/**
 * @param {number} n
 * @param {number[][]} artifacts
 * @param {number[][]} dig
 * @return {number}
 */
const digArtifacts = function (n, a, d) {
  const f = Array(n).fill(0).map(() => Array(n).fill(0))
  for (const [x, y] of d) {
    f[x][y] = 1
  }
  let ans = 0
  for (const [x1, y1, x2, y2] of a) {
    let ok = true
    for (let i = x1; i <= x2; i++) {
      for (let j = y1; j <= y2; j++) {
        if (f[i][j] === 0) {
          ok = false
          break
        }
      }
      if (!ok) break
    }
    ans += ok
  }
  return ans
}
