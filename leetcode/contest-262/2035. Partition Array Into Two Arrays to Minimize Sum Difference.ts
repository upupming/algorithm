function minimumDifference (nums: number[]): number {
  // 全部乘以 2，确保 sum / 2 是整数
  nums = nums.map(x => x * 2)
  const sum = nums.reduce((p, c) => p + c, 0)
  const n = nums.length / 2
  const l = []; const r = []
  // 选 0 个数，可能的和只有 0
  l[0] = new Set([0]); r[0] = new Set([0])
  for (let i = 0; i < n; i++) {
    // 在 0~i-1 之间，选 j 个数时，能够形成的和 l[j]
    // 在 0~i 之间，选 j+1 个数时，能够形成的和 l[j+1]
    for (let j = i; j >= 0; j--) {
      for (const val of l[j]) {
        l[j + 1] ??= new Set()
        l[j + 1].add(val + nums[i])
      }
    }
  }
  for (let i = 0; i < n; i++) {
    for (let j = i; j >= 0; j--) {
      for (const val of r[j]) {
        r[j + 1] ??= new Set()
        r[j + 1].add(val + nums[i + n])
      }
    }
  }

  // 每个个数，按照和的大小从小到大排序
  const ls = l.map(s => [...s].sort((a, b) => a - b))
  const rs = r.map(s => [...s].sort((a, b) => a - b))
  // console.log(ls, rs)
  const target = sum / 2
  let ans = 1e10
  // 双指针，从前 n 个数中选 i 个，从后 n 个数中选 n-i 个，和尽量接近 sum / 2
  for (let i = 0; i < n; i++) {
    const lenL = ls[i].length; const lenR = rs[n - i].length
    for (let pl = 0, pr = lenR - 1; pl < lenL && pr >= 0;) {
      const cur = ls[i][pl] + rs[n - i][pr]
      //                  这里不需要乘以 2，因为整个数组已经乘以 2 了
      ans = Math.min(ans, Math.abs(cur - target))
      if (cur < target) pl++
      else pr--
    }
  }
  return ans
};
