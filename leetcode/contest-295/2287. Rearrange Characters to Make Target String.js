/**
 * @param {string} s
 * @param {string} target
 * @return {number}
 */
 var rearrangeCharacters = function(s, target) {
  let cnt = Array(26).fill(0)
  let cnt1 = Array(26).fill(0)
  for (let i = 0; i < s.length; i++) {
      const x = s.charCodeAt(i) - 'a'.charCodeAt(0)
      cnt[x]++
  }
  for (let i = 0; i < target.length; i++) {
      const x = target.charCodeAt(i) - 'a'.charCodeAt(0)
      cnt1[x]++
  }
  let ans = 1e10
  for (let i = 0; i < 26; i++) {
      if (cnt1[i] > 0) ans = Math.min(ans, Math.floor(cnt[i] / cnt1[i]))
  }
  return ans
};
