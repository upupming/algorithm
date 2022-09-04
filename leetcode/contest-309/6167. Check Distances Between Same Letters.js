/**
 * @param {string} s
 * @param {number[]} distance
 * @return {boolean}
 */
const checkDistances = function (s, distance) {
  const idx = Array(26).fill(0).map(() => [])
  for (let i = 0; i < s.length; i++) {
    const ch = s.charCodeAt(i) - 'a'.charCodeAt(0)
    idx[ch].push(i)
  }
  for (let i = 0; i < 26; i++) {
    if (idx[i].length) {
      if (idx[i][1] - idx[i][0] - 1 !== distance[i]) return false
    }
  }
  return true
}
