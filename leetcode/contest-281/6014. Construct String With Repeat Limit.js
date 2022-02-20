/**
 * @param {string} s
 * @param {number} repeatLimit
 * @return {string}
 */
const repeatLimitedString = function (s, r) {
  const solve = (cnt) => {
    let ans = ''; let f = false
    for (let i = 25; i >= 0; i--) {
      if (cnt[i] === 0) continue
      if (f) {
        cnt[i] -= 1
        ans += String.fromCharCode('a'.charCodeAt(0) + i)
        return ans + solve(cnt)
      }
      if (cnt[i] > r) {
        cnt[i] -= r
        for (let j = 0; j < r; j++) ans += String.fromCharCode('a'.charCodeAt(0) + i)
        f = true
      } else {
        for (let j = 0; j < cnt[i]; j++) ans += String.fromCharCode('a'.charCodeAt(0) + i)
        cnt[i] = 0
        return ans + solve(cnt)
      }
    }
    return ans
  }

  const cnt = Array(26).fill(0)
  for (let i = 0; i < s.length; i++) {
    cnt[s[i].charCodeAt(0) - 'a'.charCodeAt(0)]++
  }
  return solve(cnt)
}
