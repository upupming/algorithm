/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
const characterReplacement = function (s, k) {
  const n = s.length; const cnt = {}
  let ans = 0
  for (let i = 0, j = 0; i < n; i++) {
    const ok = (end) => {
      cnt[s[end]] ??= 0, cnt[s[end]]++
      const maxCnt = [...Object.values(cnt)].reduce((p, c) => Math.max(p, c), 0)
      if (end - i + 1 - maxCnt <= k) {
        return true
      } else {
        cnt[s[end]]--
        return false
      }
    }
    while (j < n && ok(j)) {
      j++
    }
    ans = Math.max(ans, j - i)
    cnt[s[i]]--
  }
  return ans
}
