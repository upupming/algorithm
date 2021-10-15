/**
 * @param {string} num
 * @param {number} k
 * @return {string}
 */
const removeKdigits = function (num, k) {
  const stk = []
  for (const ch of num) {
    while (k && stk.length && ch < stk[stk.length - 1]) {
      stk.pop()
      k--
    }
    stk.push(ch)
  }
  while (k) stk.pop(), k--
  while (stk.length >= 2 && stk[0] === '0') stk.shift()
  if (stk.length === 0) stk.push(0)
  return stk.join('')
}
