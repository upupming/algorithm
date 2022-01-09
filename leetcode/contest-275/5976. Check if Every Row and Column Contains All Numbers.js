/**
 * @param {number[][]} matrix
 * @return {boolean}
 */
const checkValid = function (matrix) {
  const [n, m] = [matrix.length, matrix[0].length]
  for (let i = 0; i < n; i++) {
    const cnt = {}
    for (let j = 0; j < m; j++) {
      cnt[matrix[i][j]] ??= 0
      cnt[matrix[i][j]]++
    }
    // console.log(cnt)
    for (let j = 1; j <= n; j++) {
      if (cnt[j] == null) return false
    }
  }
  for (let i = 0; i < n; i++) {
    const cnt = {}
    for (let j = 0; j < m; j++) {
      cnt[matrix[j][i]] ??= 0
      cnt[matrix[j][i]]++
    }
    // console.log(cnt)
    for (let j = 1; j <= n; j++) {
      if (cnt[j] == null) return false
    }
  }
  return true
}
