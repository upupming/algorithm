/**
 * @param {number[][]} fruits
 * @param {number} startPos
 * @param {number} k
 * @return {number}
 */
const maxTotalFruits = function (f, s, k) {
  const sum = []
  sum[-1] = 0
  const n = f.length
  for (let i = 0, j = 0; j < n; i++) {
    if (f[j][0] === i) {
      sum[i] = sum[i - 1] + f[j][1]
      j++
    } else {
      sum[i] = sum[i - 1]
    }
  }
  while (sum.length - 1 < s) sum.push(sum[sum.length - 1])
  const m = sum.length - 1
  let ans = 0
  for (let x = Math.max(0, s - k); x <= s; x++) {
    let l = s; let r = m
    const valid = (y) => {
      const dx = s - x; const dy = y - s
      if (2 * dx + dy <= k || dx + 2 * dy <= k) return true
      return false
    }
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (valid(mid)) l = mid
      else r = mid - 1
    }
    // console.log(x, l)
    ans = Math.max(ans, sum[l] - sum[x - 1])
  }
  return ans
}
