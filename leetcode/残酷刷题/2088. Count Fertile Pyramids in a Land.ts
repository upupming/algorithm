function countPyramids (grid: number[][]): number {
  const [m, n] = [grid.length, grid[0].length]
  let ans = 0
  const dpUp: number[][] = []
  const dpDown: number[][] = []

  const [left, right]: [number[][], number[][]] = [[], []]
  for (let i = 0; i < m; i++) {
    left[i] = []; right[i] = []
    for (let j = 0; j < n; j++) {
      if (grid[i][j] === 1) left[i][j] = (left[i][j - 1] ?? 0) + 1
      else left[i][j] = 0
    }
    for (let j = n - 1; j >= 0; j--) {
      if (grid[i][j] === 1) right[i][j] = (right[i][j + 1] ?? 0) + 1
      else right[i][j] = 0
    }
  }
  for (let i = 0; i < m; i++) {
    dpUp[i] = []
    for (let j = 0; j < n; j++) {
      dpUp[i][j] = Math.min((dpUp[i - 1]?.[j] ?? 0) + 1, left[i][j], right[i][j])
      if (dpUp[i][j] > 1) ans += dpUp[i][j] - 1
    }
  }
  for (let i = m - 1; i >= 0; i--) {
    dpDown[i] = []
    for (let j = 0; j < n; j++) {
      dpDown[i][j] = Math.min((dpDown[i + 1]?.[j] ?? 0) + 1, left[i][j], right[i][j])
      if (dpDown[i][j] > 1) ans += dpDown[i][j] - 1
    }
  }
  return ans
};
