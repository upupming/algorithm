function maxValue (events: number[][], k: number): number {
/*
f[i][j] 表示参加到第 i 个活动为止，参加了 j 个事件的最大收益
对于每一个事件 i 要找到前面最后的一个收益最大的事件来进行转移

g[i][j] 表示参加到第 <=i 个活动为止，参加了 j 个事件的最大收益
*/
  const n = events.length
  const g = [...Array(n)].map(() => Array<number>(k + 1).fill(0))
  events.sort((a, b) => a[1] - b[1])
  const ans = Array(k + 1).fill(0)

  for (let i = 0; i < n; i++) {
    const [s, e, v] = events[i]
    // 找到最后一个在当前时间开始之前的事件
    let [l, r] = [0, i - 1]
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (events[mid][1] < s) l = mid
      else r = mid - 1
    }
    const prev = (events[l][1] < s) ? l : -1
    for (let j = 1; j <= k; j++) {
      const now = (prev === -1 ? 0 : g[prev][j - 1]) + v
      g[i][j] = ans[j] = Math.max(ans[j], now)
    }
  }

  return Math.max(...ans)
};
