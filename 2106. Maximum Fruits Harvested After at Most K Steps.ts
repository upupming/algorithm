function maxTotalFruits (fruits: number[][], startPos: number, k: number): number {
  // 2x + y <= k, y 增大, x 减小，双指针
  const sum: number[] = []
  sum[-1] = 0
  const n = fruits.length
  for (let i = 0, j = 0; i <= 2e5; i++) {
    sum[i] = sum[i - 1]
    while (j < n && fruits[j][0] === i) {
      sum[i] += fruits[j][1]
      j++
    }
  }

  let ans = 0
  // console.log(sum[-1])
  const update = (l: number, r: number) => {
    ans = Math.max(ans,
      sum[Math.min(r, sum.length - 1)] -
      sum[Math.max(l - 1, -1)])
  }
  for (let x = Math.floor(k / 2); x >= 0; x--) {
    const y = k - 2 * x
    // 左走 x，右走 y
    const l = startPos - x; const r = startPos + y
    update(l, r)
    // 左走 y，右走 x
    const l1 = startPos - y; const r1 = startPos + x
    update(l1, r1)
  }
  return ans
};
