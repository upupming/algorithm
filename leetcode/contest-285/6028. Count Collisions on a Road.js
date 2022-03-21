/**
 * @param {string} directions
 * @return {number}
 */
const countCollisions = function (d) {
  const s = Array.isArray(d) ? d : d.split('')
  const n = s.length
  const l = []; const r = []
  l[-1] = 'L', r[n] = 'R'
  for (let i = 0; i < n; i++) {
    l[i] = (s[i] === 'L') ? l[i - 1] : s[i]
  }
  for (let i = n - 1; i >= 0; i--) {
    r[i] = (s[i] === 'R') ? r[i + 1] : s[i]
  }
  let ans = 0; let tmp = 0
  for (let i = 0; i < n; i++) {
    if (s[i] === 'L') {
      if (l[i - 1] === 'R') {
        if (s[i - 1] === 'L') tmp += 1
        else tmp += 2
      } else if (l[i - 1] === 'S') ans += 1
    }
    if (s[i] === 'R') {
      if (r[i + 1] === 'L') {
        if (s[i + 1] === 'R') tmp += 1
        // else tmp += 2
      } else if (r[i + 1] === 'S') ans += 1
    }
    // console.log(i, s[i], ans)
  }
  return ans + tmp
}
