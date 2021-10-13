/**
 * @param {string} s
 * @return {string}
 */
const removeDuplicateLetters = function (s) {
  const cnt = s.split('').reduce((p, c) => {
    p[c] ??= 0, p[c]++
    return p
  }, {})
  const stk = []; const has = {}
  for (const ch of s) {
    if (stk.length === 0 || (ch >= stk[stk.length - 1])) {
    } else if (!has[ch]) {
      while (stk.length && ch < stk[stk.length - 1] && cnt[stk[stk.length - 1]]) {
        has[stk.pop()] = 0
      }
    }
    if (!has[ch]) {
      stk.push(ch)
      has[ch] = 1
    }
    cnt[ch]--
  }
  return stk.join('')
}
