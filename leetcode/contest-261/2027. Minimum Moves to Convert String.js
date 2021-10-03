/**
 * @param {string} s
 * @return {number}
 */
const minimumMoves = function (s) {
  let ans = 0
  for (let i = 0; i < s.length; i++) {
    if (s[i] === 'X') {
      ans++
      i += 2
    } else {

    }
  }
  return ans
}
