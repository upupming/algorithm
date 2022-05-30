/**
 * @param {string} s
 * @return {number}
 */
const uniqueLetterString = function (s) {
  const n = s.length; let ans = 0
  for (let i = 0; i < 26; i++) {
    const ch = String.fromCharCode('A'.charCodeAt(0) + i)
    const pos = []
    for (let i = 0; i < n; i++) {
      if (s[i] === ch) pos.push(i)
    }
    for (let j = 0; j < pos.length; j++) {
      const l = pos[j] - (pos[j - 1] ?? -1); const r = (pos[j + 1] ?? n) - pos[j]
      ans += l * r
    }
  }
  return ans
}
