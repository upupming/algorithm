/**
 * @param {number[]} rolls
 * @param {number} k
 * @return {number}
 */
 var shortestSequence = function(rolls, k) {
  const n = rolls.length
  let j = 0, s = new Set()
  for (let i = 0; i < n; i++) {
      s.add(rolls[i])
      if (s.size === k) {
          s.clear()
          j++
      }
  }
  return j+1
};
