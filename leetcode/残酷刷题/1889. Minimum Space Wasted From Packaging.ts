/*
暴力: 对于每个 package，选离他最近的大于他的箱子 n m log m
优化：对于每个 box，一次计算有多少 package 用这个 box，直接算出浪费空间
  时间复杂度 m log n
*/
function minWastedSpace (packages: number[], boxes: number[][]): number {
  const n = packages.length
  const sum = Array<number>(n + 1).fill(0)
  packages.sort((a, b) => a - b)
  for (let i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + packages[i - 1]
  }
  let ans = 1e11
  for (const box of boxes) {
    box.sort((a, b) => a - b)
    let i = 0
    let tmp = 0
    for (const b of box) {
      // 找打 > b 的最小的 package，这个之前的 package 都用 b 来装
      let l = i; let r = n
      while (l < r) {
        const mid = (l + r) >> 1
        if (packages[mid] > b) r = mid
        else l = mid + 1
      }
      r--
      tmp += b * (r - i + 1) - (sum[r + 1] - sum[i])
      i = r + 1
      if (i === n) break
    }
    if (i === n) {
      ans = Math.min(ans, tmp)
    }
  }
  return ans === 1e11 ? -1 : (ans % (1e9 + 7))
};
