function kthSmallest (mat: number[][], k: number): number {
  const [m, n] = [mat.length, mat[0].length]
  let sums: number[] = [...mat[0]]
  for (let i = 1; i < m; i++) {
    const tmp = []
    for (let j = 0; j < n; j++) {
      for (const a of sums) {
        tmp.push(a + mat[i][j])
      }
    }
    tmp.sort((a, b) => a - b)
    sums = tmp.slice(0, 200)
  }
  return sums[k - 1]
};
