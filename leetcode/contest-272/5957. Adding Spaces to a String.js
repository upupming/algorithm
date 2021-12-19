/**
 * @param {string} s
 * @param {number[]} spaces
 * @return {string}
 */
const addSpaces = function (s, spaces) {
  const ans = []
  let last = 0
  for (let i = 0; i < spaces.length; i++) {
    ans.push(s.slice(last, spaces[i]))
    last = spaces[i]
  }
  ans.push(s.slice(last))
  return ans.join(' ')
}
