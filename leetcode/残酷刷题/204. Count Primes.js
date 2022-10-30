/**
 * @param {number} n
 * @return {number}
 */
const countPrimes = function (n) {
  const seen = new Uint8Array(n); const p = []
  for (let i = 2; i < n; i++) {
    if (!seen[i]) p.push(i)
    for (let j = 0; p[j] <= n / i; j++) {
      seen[p[j] * i] = 1
      if (i % p[j] === 0) break
    }
  }
  return p.length
}
