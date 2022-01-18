/**
 * @param {string} s
 * @return {number}
 */
 var longestValidParentheses = function(s) {
  let ans = 0, stk = []
  for (let i = 0; i < s.length; i++) {
      if (s[i] === '(') stk.push(i)
      else {
          if (stk.length && s[stk[stk.length-1]] === '(') {
              stk.pop()
              const j = stk[stk.length-1] ?? -1
              ans = Math.max(ans, i - j)
          } else {
              stk.push(i)
          }
      }
  }
  return ans
};
