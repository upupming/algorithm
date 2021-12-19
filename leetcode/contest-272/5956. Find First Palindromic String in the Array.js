/**
 * @param {string[]} words
 * @return {string}
 */
 var firstPalindrome = function(words) {
  for (const w of words) {
      if (w === w.split('').reverse().join('')) return w
  }
  return ''
};
