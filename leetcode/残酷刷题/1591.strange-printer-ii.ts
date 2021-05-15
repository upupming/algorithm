/*
 * @lc app=leetcode id=1591 lang=typescript
 *
 * [1591] Strange Printer II
 * 逆向模拟 paint 过程，每次将一个符合条件的矩形区域变成 -1，表示可以是任何颜色
 * 如何判断是一个完整的矩形呢？可以找到 top left 和 bottom down，然后枚举这个区域即可
 * 如果有一个 -1 的赋值两种情况，选哪个呢？实际上不影响，因为我们的最终目标是所有点全部变成 -1 就行了，-1 可以和任何点匹配
 */
// @lc code=start
const _max = Math.max.bind(Math)
const _min = Math.min.bind(Math)
// const log = console.log.bind(console)
const log = (...args: any[]) => {}
// eslint-disable-next-line @typescript-eslint/no-unused-vars
export function isPrintable (targetGrid: number[][]): boolean {
  const [m, n] = [targetGrid.length, targetGrid[0].length]
  let flag
  do {
    flag = false
    // 寻找所有可能的组成矩形的颜色
    for (let color = 1; color <= 60; color++) {
      let [l, r, t, d] = [100, -1, 100, -1]
      for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
          if (targetGrid[i][j] === color) {
            l = _min(l, j)
            r = _max(r, j)
            t = _min(t, i)
            d = _max(d, i)
          }
        }
      }
      log(color, l, r, t, d)
      if (l > r || t > d) continue
      // 看这个颜色是否能组成矩形
      let ok = true
      for (let i = t; i <= d; i++) {
        for (let j = l; j <= r; j++) {
          if (targetGrid[i][j] === -1 || targetGrid[i][j] === color) continue
          ok = false
          break
        }
        if (!ok) break
      }
      // 找到了一个可行的颜色
      if (ok) {
        for (let i = t; i <= d; i++) {
          for (let j = l; j <= r; j++) {
            targetGrid[i][j] = -1
          }
        }
        flag = true
        break
      }
    }
  } while (flag)

  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (targetGrid[i][j] !== -1) return false
    }
  }
  return true
};
// @lc code=end
