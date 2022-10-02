/**
 * @param {number} num1
 * @param {number} num2
 * @return {number}
 */
const minimizeXor = function (num1, num2) {
  let s = num1.toString(2)
  let t = num2.toString(2)
  const n = Math.max(s.length, t.length)
  // console.log('s', s, typeof s, 't', t)
  s = s.padStart(n, '0').split('').map(Number)
  t = t.padStart(n, '0').split('').map(Number)
  const cnt = t.reduce((p, c) => p + c, 0)
  const ans = Array(n).fill(-1)
  let used = 0

  for (let i = 0; i < n && used < cnt; i++) {
    if (s[i] === 1) ans[i] = 1, used++
  }
  for (let i = n - 1; i >= 0 && used < cnt; i--) {
    if (ans[i] === -1) ans[i] = 1, used++
  }
  for (let i = 0; i < n; i++) {
    if (ans[i] === -1) ans[i] = 0
  }
  return parseInt(ans.join(''), 2)
}
