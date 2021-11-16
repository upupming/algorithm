function platesBetweenCandles (s: string, queries: number[][]): number[] {
  const n = s.length
  const cnt = [0]
  for (let i = 1; i <= n; i++) cnt[i] = cnt[i - 1] + Number(s[i - 1] === '*')
  const l: number[] = []; const r: number[] = []
  // l 表示当前点左边的第 1 个 |
  for (let i = 0, k = -1; i < n; i++) {
    if (s[i] === '|') k = i
    l[i] = k
  }
  for (let i = n - 1, k = n; i >= 0; i--) {
    if (s[i] === '|') k = i
    r[i] = k
  }
  return queries.map(([left, right]) => {
    const [i, j] = [r[left], l[right]]
    // console.log(i, j)
    if (i <= j) {
      // console.log(i, j, cnt[i], cnt[j + 1])
      // [i, j] 区间内的 * 的个数
      return cnt[j + 1] - cnt[i]
    } else {
      return 0
    }
  })
};
