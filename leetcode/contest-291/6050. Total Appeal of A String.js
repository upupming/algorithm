/**
 * @param {string} s
 * @return {number}
 */
const appealSum = function (s) {
  const n = s.length
  const h = {}; let cnt = 0
  for (let i = 0; i < n; i++) {
    let x = i + 1; const y = n - i
    if (h[s[i]] != null) x = i - h[s[i]]
    cnt += x * y
    // console.log(i, s[i], cnt)
    h[s[i]] = i
  }
  return cnt
}
