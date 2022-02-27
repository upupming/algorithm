/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
const minSteps = function (s, t) {
  const cnt1 = Array(26).fill(0)
  const cnt2 = Array(26).fill(0)
  for (let i = 0; i < s.length; i++) {
    cnt1[s[i].charCodeAt(0) - 'a'.charCodeAt(0)]++
  }
  for (let i = 0; i < t.length; i++) {
    cnt2[t[i].charCodeAt(0) - 'a'.charCodeAt(0)]++
  }
  let ans = 0
  for (let i = 0; i < 26; i++) {
    const m = Math.max(cnt1[i], cnt2[i])
    ans += 2 * m - cnt1[i] - cnt2[i]
  }
  return ans
}
