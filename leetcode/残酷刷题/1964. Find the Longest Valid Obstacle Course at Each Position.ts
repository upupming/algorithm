function longestObstacleCourseAtEachPosition (obstacles: number[]): number[] {
  const ans: number[] = []
  const p: number[] = []
  for (const a of obstacles) {
    let [l, r] = [0, p.length]
    while (l < r) {
      const mid = l + r >> 1
      if (mid === p.length || p[mid] > a) r = mid
      else l = mid + 1
    }
    if (l === p.length) {
      p.push(a)
      ans.push(p.length)
    }
    else {
      p[l] = a
      ans.push(l + 1)
    }
  }
  return ans
};
