/**
 * @param {string} number
 * @param {character} digit
 * @return {string}
 */
const removeDigit = function (number, digit) {
  const n = number.length
  const p = []
  for (let i = 0; i < n; i++) {
    if (number[i] === digit) {
      let tmp = number.slice(0, i) + number.slice(i + 1)
      while (tmp[0] === '0') tmp = tmp.slice(1)
      p.push(tmp)
    }
  }
  p.sort()
  return p[p.length - 1]
}
