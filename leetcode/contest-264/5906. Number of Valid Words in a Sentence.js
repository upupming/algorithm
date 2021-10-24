/**
 * @param {string} sentence
 * @return {number}
 */
const countValidWords = function (sentence) {
  const s = sentence.split(' ')
  let ans = 0
  const isChar = (ch) => ch >= 'a' && ch <= 'z'
  s.forEach(w => {
    if (w.length <= 0) return
    if (w[0] === '-' || w[w.length - 1] === '-') return
    let cnt = 0
    for (let i = 0; i < w.length; i++) {
      if (w[i] === '-') {
        if (isChar(w[i - 1]) && isChar(w[i + 1])) { cnt++ } else return
      }
      if (cnt >= 2) return
      if (w[i] >= '0' && w[i] <= '9') return
      if (w[i] === '!' || w[i] === ',' || w[i] === '.') {
        if (i !== w.length - 1) return
      }
    }
    // console.log(w)
    ans++
  })
  return ans
}
