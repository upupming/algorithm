/**
 * @param {string[]} words
 * @return {number}
 */
const longestPalindrome = function (words) {
  const cnt = {}
  for (const word of words) {
    cnt[word] ??= 0
    cnt[word]++
  }
  let ans = 0; let rest = 0
  for (const word of words) {
    const a = word; const b = a.split('').reverse().join('')
    if (a !== b && cnt[a] && cnt[b]) {
      const c = Math.min(cnt[a], cnt[b])
      cnt[a] -= c, cnt[b] -= c
      ans += c * 4
    }
    if (cnt[a] && a[0] === a[1]) {
      if (cnt[a] % 2 === 0) ans += cnt[a] * 2
      else ans += (cnt[a] - 1) * 2, rest = 2
      cnt[a] = 0
    }
  }
  return ans + rest
}
