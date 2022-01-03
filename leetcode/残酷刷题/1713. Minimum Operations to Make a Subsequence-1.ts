function minOperations (target: number[], arr: number[]): number {
  // len(target) - len(LCS)
  // LCS 可以转化成 LIS 问题，因为 target 中没有重复元素，可以计算 arr 中 idx 的 LIS 即可
  const num2Idx: Record<number, number> = {}
  target.forEach((x, idx) => num2Idx[x] = idx)
  const idxArr: number[] = []
  arr.forEach((x) => {
    if (num2Idx[x] == null) return
    idxArr.push(num2Idx[x])
  })
  const p: number[] = []
  idxArr.forEach(x => {
    let [l, r] = [0, p.length]
    while (l < r) {
      const mid = l + r >> 1
      if (mid === p.length || p[mid] >= x) r = mid
      else l = mid + 1
    }
    p[l] = x
  })
  return target.length - p.length
};
