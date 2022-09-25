/**
 * @param {string} s
 * @return {number}
 */
const longestContinuousSubstring = function (s) {
  s = s.split('').map((x) => x.charCodeAt(0) - 'a'.charCodeAt(0))
  const n = s.length
  let ans = 0
  for (let i = 0; i < n;) {
    let j = i
    while (j < n && (j === i || s[j] - s[j - 1] === 1)) j++
    ans = Math.max(ans, j - i)
    i = j
  }
  return ans
}
