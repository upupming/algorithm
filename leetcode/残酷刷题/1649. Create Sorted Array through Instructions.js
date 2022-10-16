/**
 * @param {number[]} instructions
 * @return {number}
 */
const createSortedArray = function (instructions) {
  const n = instructions.length
  instructions = instructions.reverse().map((a, idx) => [a, idx])
  const a = Array(n).fill(0); const b = Array(n).fill(0)
  const count = (i, j) => {
    if (i === j) return
    const t = i + j >> 1
    count(i, t)
    count(t + 1, j)
    for (let x = i; x <= t; x++) {
      const p = instructions[x][0]; const q = instructions[x][0]
      // >p 的第一个数
      let l = t + 1; let r = j + 1
      while (l < r) {
        const mid = l + r >> 1
        if (mid === j + 1 || instructions[mid][0] > p) r = mid
        else l = mid + 1
      }
      const p1 = l
      // < q 的最后一个数
      l = t, r = j
      while (l < r) {
        const mid = l + r + 1 >> 1
        if (mid === t || instructions[mid][0] < q) l = mid
        else r = mid - 1
      }
      const p2 = l
      const idx = instructions[x][1]
      a[idx] += j - p1 + 1
      b[idx] += p2 - t
    }

    let x = i; let y = t + 1; const tmp = []
    while (x <= t && y <= j) {
      if (instructions[x][0] <= instructions[y][0]) tmp.push(instructions[x++])
      else tmp.push(instructions[y++])
    }
    while (x <= t) tmp.push(instructions[x++])
    while (y <= j) tmp.push(instructions[y++])
    for (let k = i; k <= j; k++) instructions[k] = tmp[k - i]
  }
  count(0, n - 1)

  let ans = 0
  for (let i = 0; i < n; i++) {
    ans += Math.min(a[i], b[i])
    ans %= 1e9 + 7
  }

  return ans
}
