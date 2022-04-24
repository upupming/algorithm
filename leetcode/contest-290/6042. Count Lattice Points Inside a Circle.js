/**
 * @param {number[][]} circles
 * @return {number}
 */
const countLatticePoints = function (circles) {
  let ans = 0
  for (let i = 0; i <= 200; i++) {
    for (let j = 0; j <= 200; j++) {
      let ok = false
      for (const [x, y, r] of circles) {
        const d = (x - i) * (x - i) + (y - j) * (y - j)
        if (d <= r * r) {
          ok = true
          break
        }
      }
      ans += ok
    }
  }
  return ans
}
