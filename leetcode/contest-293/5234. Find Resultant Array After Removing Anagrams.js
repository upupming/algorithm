/**
 * @param {string[]} words
 * @return {string[]}
 */
const removeAnagrams = function (words) {
  const ans = []
  let last
  for (let i = 0; i < words.length; i++) {
    cur = words[i].split('').sort().join('')
    if (cur === last) continue
    else {
      ans.push(words[i])
      last = cur
    }
  }
  return ans
}
