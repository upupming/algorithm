/**
 * @param {number[][]} matrix
 * @return {number}
 */
const longestIncreasingPath = function (matrix) {
  const m = matrix.length; const n = matrix[0].length
  const dx = [0, 0, 1, -1]
  const dy = [1, -1, 0, 0]
  const valid = (i, j) => i >= 0 && i < m && j >= 0 && j < n
  const cache = {}
  const get = (i, j) => {
    const key = `${i}_${j}`
    if (cache[key] != null) return cache[key]
    let ans = 1
    for (let k = 0; k < 4; k++) {
      const x = i + dx[k]
      const y = j + dy[k]
      if (valid(x, y) && matrix[i][j] > matrix[x][y]) {
        ans = Math.max(ans, get(x, y) + 1)
      }
    }
    return cache[key] = ans
  }
  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      ans = Math.max(ans, get(i, j))
    }
  }
  return ans
}
