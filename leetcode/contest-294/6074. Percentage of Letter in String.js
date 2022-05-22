/**
 * @param {string} s
 * @param {character} letter
 * @return {number}
 */
 var percentageLetter = function(s, letter) {
  const n = s.length
  let cnt = 0
  for (const ch of s) {
      if (ch === letter) cnt++
  }
  return Math.floor(cnt / n * 100)
};
