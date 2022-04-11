/**
 * @param {string} s
 * @return {number}
 */

const sumScores = function (s) {
  // 最好以 1 为开始下标，比较好处理 p 数组
  const n = s.length
  s = ' ' + s

  const P = 131
  const Q = 1e4 + 7; const Q1 = 1e5 + 7
  const f = [0]; const p = [1]
  const f1 = [0]; const p1 = [1]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + ((s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q
    p[i] = p[i - 1] * P % Q

    f1[i] = (f1[i - 1] * P % Q1 + ((s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q1
    p1[i] = p1[i - 1] * P % Q1
  }
  const hash = (i, j) => {
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }
  const hash1 = (i, j) => {
    return (f1[j] - f1[i - 1] * p1[j - i + 1] % Q1 + Q1) % Q1
  }

  const h = []; const h1 = []
  h[n + 1] = h1[n + 1] = 0
  let ans = 0
  // 模拟按照从右往左构造字符串的过程
  for (let i = n; i >= 1; i--) {
    const j = n - i
    h[i] = (h[i + 1] + (s[i].charCodeAt(0) - 'a'.charCodeAt(0)) * p[j]) % Q
    h1[i] = (h1[i + 1] + (s[i].charCodeAt(0) - 'a'.charCodeAt(0)) * p1[j]) % Q1

    function valid (mid) {
      const k = i + mid - 1
      // [i, k] 长为 mid 区间的 hash 值，注意后面跟了 n-k 个空的位，因此从原串上求得hash要乘上p[n-k]
      const hs = (h[i] - h[k + 1] + Q) % Q
      const hs1 = (h1[i] - h1[k + 1] + Q1) % Q1
      const a = ((hash(1, mid) * p[n - k]) % Q === hs)
      const b = ((hash1(1, mid) * p1[n - k]) % Q1 === hs1)
      return a && b
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
