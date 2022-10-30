/**
 * @param {number[]} nums
 * @return {number}
 */
const countDifferentSubsequenceGCDs = function (nums) {
  const g = []
  const gcd = (a, b) => b ? gcd(b, a % b) : a
  for (const x of nums) {
    for (let y = 1; y <= Math.sqrt(x); y++) {
      if (x % y === 0) {
        if (g[y] == null) g[y] = x
        else g[y] = gcd(g[y], x)
        if (y != x / y) {
          if (g[x / y] == null) g[x / y] = x
          else g[x / y] = gcd(g[x / y], x)
        }
      }
    }
  }
  let ans = 0
  for (let i = 1; i <= 2e5; i++) {
    if (g[i] == i) ans++
  }
  return ans
}
