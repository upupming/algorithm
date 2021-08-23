// len(target) - len(LCS)
// 由于 target 中没有重复元素，求 LCS 可以转换为求 LIS
function minOperations(target: number[], arr: number[]): number {
  const idx: number[] = []
  for (let i = 0; i < target.length; i++) {
    idx[target[i]] = i
  }
  const a: number[] = []
  for (const x of arr) {
    if (idx[x] !== undefined) {
      a.push(idx[x])
    }
  }
  const p: number[] = []
  for (const x of a) {
    let [l, r] = [0, p.length]
    while (l < r) {
      const mid = l + r >> 1
      if (mid === p.length || p[mid] >= x) r = mid
      else l = mid + 1
    }
    p[l] = x
  }
  return target.length - p.length
};
