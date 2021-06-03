/*
枚举所有半径、中心、求和，时间复杂度 O(n * nm * n)
*/
function getBiggestThree (grid: number[][]): number[] {
  const [m, n] = [grid.length, grid[0].length]
  const ans = new Set<number>()
  for (let r = 0; r < Math.min(m, n); r++) {
    for (let i = r; i + r < m; i++) {
      for (let j = r; j + r < n; j++) {
        const [T, D, L, R] = [i - r, i + r, j - r, j + r]
        let sum = 0
        // 左上角斜线
        for (let I = T; I <= i; I++) {
          const J = T + j - I
          sum += grid[I][J]
        }
        // 左下角斜线
        for (let I = i; I <= D; I++) {
          const J = D + j - I
          sum += grid[I][J]
        }
        // 右上角斜线
        for (let I = T; I <= i; I++) {
          const J = j - T + I
          sum += grid[I][J]
        }
        // 右下角斜线
        for (let I = i; I <= D; I++) {
          const J = j - D + I
          sum += grid[I][J]
        }
        // r = 0 的特殊情况
        if (r === 0) sum /= 4
        else {
          sum -= grid[T][j] + grid[i][L] + grid[D][j] + grid[i][R]
        }
        ans.add(sum)
      }
    }
  }
  return [...ans].sort((a, b) => b - a).slice(0, 3)
};
