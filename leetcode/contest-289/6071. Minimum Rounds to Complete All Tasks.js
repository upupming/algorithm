/**
 * @param {number[]} tasks
 * @return {number}
 */
const minimumRounds = function (tasks) {
  const cnt = {}
  for (const t of tasks) {
    cnt[t] = (cnt[t] ?? 0) + 1
  }
  let ans = 0
  for (const v of Object.values(cnt)) {
    let x = Math.floor(v / 3)
    const y = Math.floor(v % 3)
    if (y === 2) x += 1
    else if (y === 1) {
      if (x === 0) return -1
      else x += 1
    }
    ans += x
  }
  return ans
}
