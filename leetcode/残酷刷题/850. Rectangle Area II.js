/**
 * @param {number[][]} rectangles
 * @return {number}
 */
const rectangleArea = function (rs) {
  const P = BigInt(1e9 + 7)
  const s = new Set()
  for (const r of rs) {
    for (let i = 0; i < 4; i++) s.add(r[i])
  }
  const nums = [...s].sort((a, b) => a - b)
  const map = {}
  for (let i = 0; i < nums.length; i++) map[nums[i]] = i
  const m = nums.length
  const diff = [...Array(m)].map(() => Array(m).fill(0))
  const f = [...Array(m + 1)].map(() => Array(m + 1).fill(0))
  for (const r of rs) {
    const h = []
    for (let i = 0; i < 4; i++) h[i] = map[r[i]]
    const [x0, y0, x1, y1] = h
    diff[x0][y0] += 1
    diff[x1][y0] -= 1
    diff[x0][y1] -= 1
    diff[x1][y1] += 1
  }
  // console.log(nums, diff)
  let ans = 0n
  for (let i = 1; i < m; i++) {
    for (let j = 1; j < m; j++) {
      f[i][j] = diff[i - 1][j - 1] + f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1]
      if (f[i][j] > 0) {
        const [x0, x1, y0, y1] = [nums[i - 1], nums[i], nums[j - 1], nums[j]]
        ans += BigInt(x1 - x0) * BigInt(y1 - y0)
        ans %= P
      }
    }
  }
  return Number(ans)
}
