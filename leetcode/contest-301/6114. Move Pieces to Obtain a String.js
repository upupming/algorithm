/**
 * @param {string} start
 * @param {string} target
 * @return {boolean}
 */
const canChange = function (s, t) {
  const ca = s.split('').filter(x => x != '_').join('') === t.split('').filter(x => x != '_').join('')
  if (!ca) return false
  let a = []; let b = []
  for (let i = 0; i < s.length; i++) {
    if (s[i] === 'L') a.push(i)
    if (t[i] === 'L') b.push(i)
  }
  if (a.length !== b.length) return false
  for (let i = 0; i < a.length; i++) if (!(a[i] >= b[i])) return false

  a = [], b = []
  for (let i = 0; i < s.length; i++) {
    if (s[i] === 'R') a.push(i)
    if (t[i] === 'R') b.push(i)
  }
  if (a.length !== b.length) return false
  for (let i = 0; i < a.length; i++) if (!(a[i] <= b[i])) return false

  return true
}
