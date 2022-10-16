/**
 * @param {number} num
 * @return {boolean}
 */
const sumOfNumberAndReverse = function (num) {
  for (let i = 0; i <= num; i++) {
    const j = Number(i.toString().split('').reverse().join(''))
    if (i + j === num) return true
  }
  return false
}
