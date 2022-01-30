/**
 * @param {string} s
 * @param {number} power
 * @param {number} modulo
 * @param {number} k
 * @param {number} hashValue
 * @return {string}
 */
const subStrHash = function (s, pp, m, k, h) {
  const n = s.length
  s = ' ' + s.split('').reverse().join('')

  const P = BigInt(pp)
  const Q = BigInt(m)
  const f = [0n]; const p = [1n]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)) + 1n)) % Q
    p[i] = p[i - 1] * P % Q
  }
  const getHash = (i, j) => {
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }
  let ans = ''
  for (let i = 1; i + k - 1 <= n; i++) {
    const j = i + k - 1
    const hash = getHash(i, j)
    if (hash === BigInt(h)) ans = s.slice(i, j + 1)
  }
  return ans.split('').reverse().join('')
}
