/**
 * @param {string} s
 * @return {number}
 */
const minimumTime = function (s) {
  const n = s.length
  const l = Array(n).fill(0); const r = Array(n).fill(0)
  l[-1] = r[n] = 0
  for (let i = 0; i < n; i++) {
    l[i] = l[i - 1]
    if (s[i] === '1') {
      l[i] = Math.min(l[i - 1] + 2, i + 1)
    }
  }
  let ans = 1e6
  for (let i = n - 1; i >= 0; i--) {
    r[i] = r[i + 1]
    if (s[i] === '1') {
      r[i] = Math.min(r[i + 1] + 2, n - i)
    }

    ans = Math.min(ans, l[i - 1] + r[i])
  }

  return ans
}
