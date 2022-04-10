function maximumBeauty (flowers: number[], newFlowers: number, target: number, full: number, partial: number): number {
  flowers.sort((a, b) => a - b)
  const n = flowers.length
  const sum: number[] = []
  sum[-1] = 0
  let idx = -1
  for (let i = 0; i < n; i++) {
    sum[i] = sum[i - 1] + Math.min(flowers[i], target)
    if (flowers[i] < target) idx = i
  }
  let ans = 0
  // [i, n) 增加到 target
  for (let i = n; i >= 0; i--) {
    const a1 = (n - i) * target - (sum[n - 1] - sum[i - 1])
    if (a1 > newFlowers) break
    const a2 = newFlowers - a1
    let l = 0; let r = target - 1
    while (l < r) {
      const mid = (l + r + 1) >> 1
      if (valid(mid)) l = mid
      else r = mid - 1
    }
    ans = Math.max(ans, (n - i) * full + l * partial)
    // console.log(n - i, l, ans)

    function valid (mid: number) {
    // 已经全都 >= target 了
      const K = Math.min(idx, i - 1)
      if (K === -1) return false
      // 找到 <= mid 的最右边的数，判断区间需要多少花费变成全部 >= mid
      let l = 0; let r = K
      while (l < r) {
        const m = l + r + 1 >> 1
        if (flowers[m] < mid) l = m
        else r = m - 1
      }
      const cost = (l + 1) * mid - sum[l]
      // console.log(i, a1, a2, idx, l, mid, cost)
      return cost <= a2
    }
  }
  return ans
};
// n log{n log{n}}
export declare const a: string
