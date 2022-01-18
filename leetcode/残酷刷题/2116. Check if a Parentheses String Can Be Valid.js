/**
 * @param {string} s
 * @param {string} locked
 * @return {boolean}
 */
const canBeValid = function (s, locked) {
  let min = 0; let max = 0
  for (let i = 0; i < s.length; i++) {
    if (locked[i] === '0') {
      // * 全部变成 )
      min--
      // * 全部变成 (
      max++
    } else {
      if (s[i] === '(') min++, max++
      else min--, max--
    }

    // ())，右括号太多了，尝试变成左括号
    if (min < 0) min += 2
    // 右括号无法找到左边的匹配的括号
    if (max < 0) return false
  }
  //
  return min === 0
}
