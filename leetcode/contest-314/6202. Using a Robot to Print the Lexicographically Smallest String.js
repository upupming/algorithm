/**
 * @param {string} s
 * @return {string}
 */
const robotWithString = function (s) {
  s = s.split('')
  const n = s.length
  const min = []; let ans = ''
  min[n] = n, s[n] = String.fromCharCode('z'.charCodeAt(0) + 1)
  for (let i = n - 1; i >= 0; i--) {
    if (s[i] <= s[min[i + 1]]) min[i] = i
    else min[i] = min[i + 1]
  }
  // console.log(min)
  const stk = []
  let i = min[0]
  for (let j = 0; j <= i; j++) stk.push(s[j])
  while (i < n) {
    ans += stk.pop()
    oldI = i
    i = min[i + 1]
    while (stk.length && stk[stk.length - 1] <= s[i]) ans += stk.pop()
    for (let j = oldI + 1; j <= i; j++) stk.push(s[j])
  }
  while (stk.length) ans += stk.pop()
  return ans.slice(0, -1)
//     "bdevfziy"
}
