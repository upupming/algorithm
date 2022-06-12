/**
 * @param {number[][]} brackets
 * @param {number} income
 * @return {number}
 */
const calculateTax = function (b, inn) {
  let ans = 0
  for (let i = 0; i < b.length; i++) {
    const [x, y] = b[i]
    if (inn >= x) ans += (x - (b[i - 1]?.[0] ?? 0)) * y / 100
    else {
      ans += (inn - (b[i - 1]?.[0] ?? 0)) * y / 100
      break
    }
  }
  return ans
}
