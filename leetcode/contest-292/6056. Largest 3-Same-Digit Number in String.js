/**
 * @param {string} num
 * @return {string}
 */
const largestGoodInteger = function (num) {
  let ans = ''; let m = -1
  for (let i = 0; i <= num.length - 3; i++) {
    const x = num.charCodeAt(i) - '0'.charCodeAt(0)
    if (x > m && num[i] === num[i + 1] && num[i] === num[i + 2]) {
      ans = num.slice(i, i + 3)
      m = x
    }
  }
  return ans
}
