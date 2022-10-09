/**
 * @param {number[]} nums
 * @return {number[]}
 */
const replaceNonCoprimes = function (nums) {
  const s = []
  const gcd = (a, b) => b ? gcd(b, a % b) : a
  for (let a of nums) {
    if (!s.length) {
      s.push(a)
      continue
    }
    let b = s[s.length - 1]
    let d = gcd(a, b)

    while (s.length && d > 1) {
      s.pop()
      a = a / d * b, b = s[s.length - 1]
      d = gcd(a, b)
    }
    s.push(a)
  }
  return s
}
