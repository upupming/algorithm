/**
 * @param {number} n
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @return {number}
 */
const gcd = (a, b) => b ? gcd(b, a % b) : a
const lcm = (a, b) => a * b / gcd(a, b)
const nthUglyNumber = function (n, a, b, c) {
  const min = BigInt(Math.min(a, b, c))
  n = BigInt(n), a = BigInt(a), b = BigInt(b), c = BigInt(c)
  let l = 1n; let r = n * min
  while (l < r) {
    const mid = l + r >> 1n
    if (valid(mid)) r = mid
    else l = mid + 1n
  }
  function valid (m) {
    const cnt = (d) => m / d
    return (cnt(a) + cnt(b) + cnt(c) - cnt(lcm(a, b)) - cnt(lcm(b, c)) - cnt(lcm(a, c)) + cnt(lcm(lcm(a, b), c))) >= n
  }
  return l
}
