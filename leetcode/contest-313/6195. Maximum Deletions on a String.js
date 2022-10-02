/**
 * @param {string} s
 * @return {number}
 */
const deleteString = function (s) {
  // 最好以 1 为开始下标，比较好处理 p 数组
  const n = s.length
  s = ' ' + s

  const P = 131n
  const Q = 1n << 64n
  const f = [0n]; const p = [1n]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q
    p[i] = p[i - 1] * P % Q
  }
  const hash = (i, j) => {
    // 乘完之后的取模非常重要，漏掉就会 WA（出现较小负数导致 + 一个 Q 不够）
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }

  const dp = Array(n + 1).fill(1)

  for (let i = n; i >= 1; i--) {
    for (let len = 1; i + (len * 2) - 1 <= n; len++) {
      // [i, j]; [j+1, k]
      const j = i + len - 1; const k = i + (len * 2) - 1
      if (hash(i, j) === hash(j + 1, k)) {
        dp[i] = Math.max(dp[i], dp[j + 1] + 1)
      }
    }
  }
  return dp[1]
}
