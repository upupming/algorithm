/**
 * @param {number} target
 * @param {number} maxDoubles
 * @return {number}
 */
 var minMoves = function(t, m) {
  let ans = 0
  while (t > 1) {
      if (t % 2 === 0 && m) {
          m--
          t /= 2
          ans++
      } else if(m == 0) {
          return ans+t-1
      } else {
          t--
          ans++
      }
  }
  return ans
};
