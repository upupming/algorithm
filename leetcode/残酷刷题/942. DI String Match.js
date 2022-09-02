/**
 * @param {string} s
 * @return {number[]}
 */
 var diStringMatch = function(s) {
  s = 'I' + s
  let max = -1, ans = []
  for (let i = 0; i < s.length; i) {
      let j = i+1
      while (j < s.length && s[j] === 'D') j++
      let k = j-i
      for (let x = max+k; x >= max+1; x--) {
          ans.push(x)
      }
      i = j, max += k
  }
  return ans
};
