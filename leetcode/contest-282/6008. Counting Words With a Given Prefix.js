/**
 * @param {string[]} words
 * @param {string} pref
 * @return {number}
 */
 var prefixCount = function(words, pref) {
  let ans = 0
  for (const w of words) {
      if (w.startsWith(pref)) ans++
  }
  return ans
};
