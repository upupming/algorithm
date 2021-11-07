/**
 * @param {string} word
 * @return {number}
 */
 var countVowelSubstrings = function(word) {
  const n = word.length
  const ok = (s) => {
      const t = new Set()
      for (const ch of s) {
          if ('aeiou'.includes(ch)) t.add(ch)
          else return false
      }
      return t.size === 5
  }
  let ans = 0
  for (let i = 0; i < n; i++) {
      for (let j = i; j < n; j++) {
          const s = word.slice(i, j + 1)
          if (ok(s)) {
              // console.log(s)
              ans++
          }
      }
  }
  return ans
};
