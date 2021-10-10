/**
 * @param {number[][]} grid
 * @param {number} x
 * @return {number}
 */
 var minOperations = function(grid, x) {
  const a = grid.flat().sort((a, b) => a - b)
  const n = a.length, mid = a[Math.floor(n/2)]
  if (n === 1) return 0
   console.log(a)
  let ans = 0
  for (const y of a) {
      let diff = Math.abs(mid - y)
      if (diff % x !== 0) {
          // console.log(mid, y, diff)
          return -1
      }
      else ans += diff / x
  }
   return ans
};
