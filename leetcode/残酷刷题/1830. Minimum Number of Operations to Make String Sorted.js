function qpow (a, b, p) {
  a = BigInt(a), b = BigInt(b), p = BigInt(p)
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = (ans * a) % p
    a = (a * a) % p
    b >>= 1n
  }
  return Number(ans % p)
}
/**
* @param {string} s
* @return {number}
*/
const makeStringSorted = function (s) {
  // 就是求 s 在所有全排列中的字典序
  const cnt = Array(26).fill(0)
  s = s.split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0))
  for (const x of s) {
    cnt[x]++
  }
  const n = s.length; const P = 1e9 + 7
  let ans = 0; let r = n - 1
  const frac = [1]; const g = []
  for (let i = 1; i <= n; i++) frac[i] = Number(BigInt(frac[i - 1]) * BigInt(i) % BigInt(P))
  for (let i = 0; i <= n; i++) g[i] = qpow(frac[i], P - 2, P)
  for (const x of s) {
    // 这一位上放 < x 的数
    let a = 0
    for (let i = 0; i < x; i++) a += cnt[i]
    let tmp = Number(BigInt(a) * BigInt(frac[r]) % BigInt(P))
    for (let i = 0; i < 26; i++) {
      tmp = Number((BigInt(tmp) * BigInt(g[cnt[i]])) % BigInt(P))
    }
    ans = (ans + tmp) % P
    // 这一位上放 === x，就继续循环
    cnt[x]--, r--
  }
  return ans
}
