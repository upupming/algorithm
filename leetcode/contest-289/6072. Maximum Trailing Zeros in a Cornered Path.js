/**
 * @param {number[][]} grid
 * @return {number}
 */
const maxTrailingZeros = function (grid) {
  const m = grid.length; const n = grid[0].length
  let ans = 0; const base = 1e7
  const sr = []; const sc = []
  const cnt = (a) => {
    let c2 = 0; let c5 = 0
    while (a % 2 === 0) a /= 2, c2++
    while (a % 5 === 0) a /= 5, c5++
    return [c2, c5]
  }
  const get = (i, j, k) => {
    return cnt(grid[i][j])[k]
  }
  for (let j = 1; j <= n; j++) {
    sr[j] = [0]
    for (let i = 1; i <= m; i++) {
      sr[j][i] = sr[j][i - 1] + get(i - 1, j - 1, 0) * base + get(i - 1, j - 1, 1)
    }
  }
  for (let i = 1; i <= m; i++) {
    sc[i] = [0]
    for (let j = 1; j <= n; j++) {
      sc[i][j] = sc[i][j - 1] + get(i - 1, j - 1, 0) * base + get(i - 1, j - 1, 1)
    }
  }
  // 枚举转角点
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      for (const [rs, re] of [[1, i], [i, m]]) {
        // 避免重复计算 [i, j] 这个点
        for (const [cs, ce] of [[1, j - 1], [j + 1, n]]) {
          const a = (Math.floor(sr[j][re] / base) - Math.floor(sr[j][rs - 1] / base)) + (sc[i][ce] / base - sc[i][cs - 1] / base)
          const b = (Math.floor(sr[j][re] % base) - Math.floor(sr[j][rs - 1] % base)) + (sc[i][ce] % base - sc[i][cs - 1] % base)
          ans = Math.max(ans, Math.min(a, b))
        }
      }
    }
  }
  return ans
}
