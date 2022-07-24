/**
 * @param {string} s
 * @return {character}
 */
 var repeatedCharacter = function(s) {
  const cnt = {}
  for (const ch of s) {
      cnt[ch] ??=0
      cnt[ch]++
      if (cnt[ch] >= 2) return ch
  }
};
