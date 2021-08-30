function maxProduct (s: string): number {
  const m = s.length
  s = `!${s}@`
  const p: number[] = []
  let [rt, mid] = [0, 0]
  for (let i = 1; i <= m; i++) {
    p[i] = i < rt ? Math.min(p[2 * mid - i], rt - i) : 1
    while (s[i + p[i]] === s[i - p[i]]) p[i]++
    if (i + p[i] > rt) {
      rt = i + p[i]
      mid = i
    }
    console.log(i, s[i], p[i])
  }
  // left[i] 表示在 [1~i] 范围内，以 i 结尾的最长奇数长回文串长度
  const [left, right] = [[0], [0]]
  let ans = 0
  for (let i = 1, j = 1; i <= m; i++) {
    while (j <= m && j + p[j] - 1 < i) j++
    left[i] = Math.max(left[i - 1], (i - j) * 2 + 1)
  }
  for (let i = m, j = m; i >= 1; i--) {
    while (j >= 1 && j - p[j] + 1 > i) j--
    right[i] = Math.max(right[i + 1] ?? 0, (j - i) * 2 + 1)
    ans = Math.max(ans, right[i] * left[i - 1])
  }
  return ans
};
