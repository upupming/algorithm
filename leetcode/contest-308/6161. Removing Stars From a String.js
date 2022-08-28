/**
 * @param {string} s
 * @return {string}
 */
const removeStars = function (s) {
  const t = []
  for (const ch of s) {
    if (ch === '*' && t.length) t.pop()
    else t.push(ch)
  }
  return t.join('')
}
