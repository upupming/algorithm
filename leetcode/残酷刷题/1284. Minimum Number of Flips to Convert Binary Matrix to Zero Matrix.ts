function minFlips (mat: number[][]): number {
  // 从全 0 开始，dp 求一下最后到达初始状态需要的最少步数
  const [m, n] = [mat.length, mat[0].length]
  const f = Array(1 << m * n).fill(1e10)
  const modify = (s: number, i: number, j: number) => {
    const [dx, dy] = [[0, 1, -1, 0, 0], [0, 0, 0, 1, -1]]
    for (let k = 0; k < 5; k++) {
      const [x, y] = [i + dx[k], j + dy[k]]
      if (x >= 0 && x < m && y >= 0 && y < n) {
        s |= 1 << (i * n + j)
      }
    }
    return s
  }
  dfs(0, 0)
  const ans = f[Number(mat.flat().reverse().join(''))]
  return ans === 1e10 ? -1 : ans
  function dfs (cur: number, dep: number) {
    if (f[cur] <= dep) return
    f[cur] = dep
    for (let i = 0; i < m; i++) {
      for (let j = 0; j < n; j++) {
        dfs(modify(cur, i, j), dep + 1)
      }
    }
  }
};
