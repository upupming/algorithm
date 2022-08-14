/**
 * @param {number} n
 * @return {number}
 */
const countNumbersWithUniqueDigits = function (n) {
  if (n === 0) return 1
  if (n === 1) return 10
  let ans = 10; let cur = 9
  for (let i = 0; i < n - 1; i++) {
    cur *= 9 - i
    ans += cur
  }
  return ans
}
