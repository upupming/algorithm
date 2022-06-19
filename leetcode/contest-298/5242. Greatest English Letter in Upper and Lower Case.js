/**
 * @param {string} s
 * @return {string}
 */
 var greatestLetter = function(s) {
  const st = new Set()
  for (let i = 0; i < 26; i++) {
      const x = String.fromCharCode('a'.charCodeAt(0)+i)
      const X = String.fromCharCode('A'.charCodeAt(0)+i)
      if (s.includes(x) && s.includes(X)) st.add(i)
  }
  let ans = '', max = -1
  for (const i of st) {
      if (i > max) {
          max = i
          ans = String.fromCharCode('A'.charCodeAt(0)+i)
      }
  }
  return ans
};
