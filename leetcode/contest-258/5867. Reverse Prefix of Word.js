/**
 * @param {string} word
 * @param {character} ch
 * @return {string}
 */
const reversePrefix = function (word, ch) {
  const i = word.indexOf(ch)
  return word.slice(0, i + 1).split('').reverse().join('') + word.slice(i + 1)
}
