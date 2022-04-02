/**
 * @param {number} start
 * @param {number} goal
 * @return {number}
 */
const minBitFlips = function (start, goal) {
  const a = start.toString(2).split('')
  const b = goal.toString(2).split('')
  while (a.length < b.length) a.unshift('0')
  while (b.length < a.length) b.unshift('0')
  let ans = 0
  for (let i = 0; i < a.length; i++) {
    if (a[i] !== b[i]) ans++
  }
  return ans
}
