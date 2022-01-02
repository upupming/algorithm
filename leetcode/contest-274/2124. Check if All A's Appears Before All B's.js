/**
 * @param {string} s
 * @return {boolean}
 */
 var checkString = function(s) {
  let x = 1e9, y = -1
  for (let i = 0; i < s.length; i++) {
      if(s[i] === 'b') x = Math.min(x, i)
      if(s[i] === 'a') y = Math.max(y, i)
  }
  return y <= x
};
