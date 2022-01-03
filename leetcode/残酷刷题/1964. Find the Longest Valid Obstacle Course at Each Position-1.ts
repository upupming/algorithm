function longestObstacleCourseAtEachPosition (obstacles: number[]): number[] {
  const p: number[] = []
  return obstacles.map((x) => {
    let [l, r] = [0, p.length]
    while (l < r) {
      const mid = l + r >> 1
      if (mid === p.length || p[mid] > x) r = mid
      else l = mid + 1
    }
    p[l] = x
    return l + 1
  })
};
