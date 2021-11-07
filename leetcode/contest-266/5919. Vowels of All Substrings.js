/**
 * @param {string} word
 * @return {number}
 */
 var countVowels = function(word) {
  const n = word.length
  let ans = 0
  for (let i = 0; i < n; i++) {
      const ch = word[i]
      if ('aeiou'.includes(ch)) {
          const l = i, r = n - 1 - i
          ans += l + r + 1 + l * r
      }
  }
  return ans
};
