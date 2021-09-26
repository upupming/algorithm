/**
 * @param {number[][]} grid
 * @return {number}
 */
const gridGame = function (grid) {
  const n = grid[0].length
  const p = [0]; const q = [0]
  for (let i = 0; i < n; i++) {
    p[i + 1] = p[i] + grid[0][i]
    q[i + 1] = q[i] + grid[1][i]
  }
  let ans = 1e10
  for (let i = 1; i <= n; i++) {
    const tmp = Math.max(q[i - 1], p[n] - p[i])
    ans = Math.min(ans, tmp)
  }
  return ans
}
