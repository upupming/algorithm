/**
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
const commonFactors = function (a, b) {
  let ans = 0
  for (let i = 1; i <= Math.floor(Math.sqrt(a)); i++) {
    if (a % i === 0) {
      if (b % i === 0)ans++
      if (a / i !== i && b % (a / i) === 0)ans++
    }
  }
  return ans
}
