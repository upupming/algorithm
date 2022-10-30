/**
 * @param {number[][]} queries
 * @return {number[]}
 */
const waysToFillArray = function (queries) {
  const ans = []; const N = 1e4 + 15; const P = BigInt(1e9 + 7)
  const c = Array(N).fill(0).map(() => Array(15).fill(0n))
  const v = {}; const p = []
  for (let i = 2; i <= N; i++) {
    if (v[i]) continue
    p.push(i)
    for (let j = i; j <= N / i; j++) v[i * j] = 1
  }
  for (let i = 0; i < N; i++) {
    c[i][0] = 1n
    for (let j = 1; j <= Math.min(i, 14); j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P
    }
  }
  for (let [n, k] of queries) {
    let s = 1n
    for (let i = 0; p[i] <= k; i++) {
      let t = 0
      while (k % p[i] === 0) t++, k /= p[i]
      s = s * c[n + t - 1][t] % P
    }
    ans.push(Number(s))
  }
  return ans
}
