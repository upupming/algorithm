/**
 * @param {number[]} plants
 * @param {number} capacityA
 * @param {number} capacityB
 * @return {number}
 */
const minimumRefill = function (p, a, b) {
  const n = p.length
  let ca = a; let cb = b
  let ans = 0
  for (let i = 0, j = n - 1; i <= j; i++, j--) {
    if (i === j) {
      // console.log(ca, cb, p[i])
      if (ca >= cb && ca >= p[i]) ca -= p[i]
      else if (ca < cb && cb >= p[i]) cb -= p[i]
      else ans++
    } else {
      // A
      if (p[i] > ca) ca = a, ans++
      ca -= p[i]
      // B
      if (p[j] > cb) cb = b, ans++
      cb -= p[j]
    }
  }
  return ans
}
