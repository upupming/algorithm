function kClosest (points: number[][], k: number): number[][] {
  const dist = (p: number[]) => p[0] * p[0] + p[1] * p[1]
  const less = (a: number[], b: number[]) => dist(a) < dist(b)
  quickSelect(0, points.length - 1, k)
  return points.slice(0, k)
  function quickSelect (l: number, r: number, k: number): number[] {
    if (l >= r) return points[l]
    let [i, j, q] = [l - 1, r + 1, points[l + r >> 1]]
    while (i < j) {
      do i++; while (less(points[i], q))
      do j--; while (less(q, points[j]))
      if (i < j) [points[i], points[j]] = [points[j], points[i]]
    }
    const cnt = j - l + 1
    if (cnt >= k) return quickSelect(l, j, k)
    else return quickSelect(j + 1, r, k - cnt)
  }
};
