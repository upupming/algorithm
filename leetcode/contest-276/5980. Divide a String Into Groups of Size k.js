/**
 * @param {string} s
 * @param {number} k
 * @param {character} fill
 * @return {string[]}
 */
 var divideString = function(s, k, fill) {
  const ans = []
  for (let i = 0; i < s.length; i+=k) {
      let t = s.slice(i, i+k)
      while (t.length < k) t += fill
      ans.push(t)
  }
  return ans
};
