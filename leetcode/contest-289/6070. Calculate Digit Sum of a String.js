/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
const digitSum = function (s, k) {
  while (s.length > k) {
    let t = ''
    for (let i = 0; i < s.length; i += k) {
      const tmp = s.slice(i, i + k).split('').map(Number)
      const sum = tmp.reduce((p, c) => p + c, 0)
      t += sum
    }
    s = t
  }
  return s
}
