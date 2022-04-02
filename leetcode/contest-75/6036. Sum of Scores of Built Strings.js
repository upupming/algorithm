/**
 * @param {string} s
 * @return {number}
 */

const sumScores = function (s) {
  // 最好以 1 为开始下标，比较好处理 p 数组
  const n = s.length
  s = ' ' + s

  const P = 131n
  const Q = 1333333331n
  const f = [0n]; const p = [1n]; const q = [1n]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q
    p[i] = p[i - 1] * P % Q
  }
  const hash = (i, j) => {
    // 乘完之后的取模非常重要，漏掉就会 WA（出现较小负数导致 + 一个 Q 不够）
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }

  const h = []
  h[n + 1] = 0n
  let ans = 0
  // 模拟按照从右往左构造字符串的过程
  for (let i = n; i >= 1; i--) {
    const j = n - i
    h[i] = (h[i + 1] + BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)) * p[j]) % Q

    function valid (mid) {
      const k = i + mid - 1
      // [i, k] 长为 mid 区间的 hash 值，注意后面跟了 n-k 个空的位，因此从原串上求得hash要乘上p[n-k]
      const hs = (h[i] - h[k + 1] + Q) % Q
      return ((hash(1, mid) * p[n - k]) % Q === hs)
    }

    // 二分可以匹配的最大长度
    let l = 0; let r = n - i + 1
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (valid(mid)) l = mid
      else r = mid - 1
    }
    ans += l
  }

  return ans
}
