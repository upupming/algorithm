function lengthOfLIS (nums: number[]): number {
  const p: number[] = []
  nums.forEach(x => {
    let [l, r] = [0, p.length]
    // 找到第一个 >= x 的地方并且替换
    while (l < r) {
      const mid = l + r >> 1
      if (p[mid] >= x || mid === p.length) r = mid
      else l = mid + 1
    }
    p[l] = x
  })
  return p.length
};
