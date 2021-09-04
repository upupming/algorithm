function minimizeTheDifference (mat: number[][], target: number): number {
  const [m, n] = [mat.length, mat[0].length]
  const filter = (arr: number[]) => {
    let minGreaterThanTarget = 1e10
    for (let j = 0; j < arr.length; j++) {
      if (arr[j] > target) {
        minGreaterThanTarget = Math.min(minGreaterThanTarget, arr[j])
      }
    }
    return arr.filter(x => x <= minGreaterThanTarget)
  }
  let sums = filter([...mat[0]])

  for (let i = 1; i < m; i++) {
    const sumsNext = new Set<number>()
    for (let j = 0; j < n; j++) {
      for (const x of sums) {
        sumsNext.add(x + mat[i][j])
      }
    }
    sums = filter([...sumsNext])
  }
  return Math.min(...sums.map((x) => Math.abs(x - target)))
};
