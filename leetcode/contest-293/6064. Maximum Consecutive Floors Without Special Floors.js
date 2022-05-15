/**
 * @param {number} bottom
 * @param {number} top
 * @param {number[]} special
 * @return {number}
 */
const maxConsecutive = function (b, t, s) {
  s.sort((a, b) => a - b)
  s.push(1e10)
  const n = s.length
  let ans = 0
  for (let i = 0; i < n; i++) {
    if (s[i] <= b) continue
    if (s[i] > t) {
      ans = Math.max(ans, t - Math.max(s[i - 1] + 1, b) + 1)
      break
    }

    let last = b
    if (i > 0) last = Math.max(s[i - 1] + 1, b)
    const len = s[i] - last
    ans = Math.max(ans, len)
    // console.log(i, last, s[i], len, ans)
  }
  return ans
}
