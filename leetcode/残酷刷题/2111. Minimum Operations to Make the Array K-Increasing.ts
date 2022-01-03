function kIncreasing (arr: number[], k: number): number {
  const n = arr.length
  let ans = 0
  for (let i = 0; i < k; i++) {
    const p: number[] = []
    let tot = 0
    // 最长单调不降子序列
    for (let j = i; j < n; j += k, tot++) {
      let [l, r] = [0, p.length]
      while (l < r) {
        const mid = l + r >> 1
        if (mid === p.length || p[mid] > arr[j]) r = mid
        else l = mid + 1
      }
      p[l] = arr[j]
    }
    ans += tot - p.length
  }
  return ans
};
