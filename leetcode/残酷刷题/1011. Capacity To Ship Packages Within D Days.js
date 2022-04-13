/**
 * @param {number[]} weights
 * @param {number} days
 * @return {number}
 */
const shipWithinDays = function (weights, days) {
  let l = 1; let r = 1e10
  const n = weights.length
  const valid = (mid) => {
    let cnt = 1
    for (let i = 0, j = mid; i < n; i++) {
      if (j < weights[i]) {
        j = mid
        cnt++
      }
      j -= weights[i]
      if (j < 0) return false
    }
    return cnt <= days
  }
  while (l < r) {
    const mid = l + r >> 1
    if (valid(mid)) r = mid
    else l = mid + 1
  }
  return l
}
