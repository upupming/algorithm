/**
 * @param {number[]} nums
 * @return {number[]}
 */
const gcd = (a, b) => b ? gcd(b, a % b) : a
const replaceNonCoprimes = function (nums) {
  const s = []
  for (let i = 0; i < nums.length; i++) {
    s.push(nums[i])
    while (s.length >= 2) {
      const a = s[s.length - 1]
      const b = s[s.length - 2]
      const g = gcd(a, b)
      if (g > 1) {
        s.pop()
        s.pop()
        s.push(a * b / g)
      } else break
    }
  }
  return s
}
