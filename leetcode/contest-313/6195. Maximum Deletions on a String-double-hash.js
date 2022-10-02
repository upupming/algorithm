/**
 * @param {string} s
 * @return {number}
 */
const deleteString = function (s) {
  // 最好以 1 为开始下标，比较好处理 p 数组
  const n = s.length
  s = ' ' + s

  const P = 131
  // 三哈希（双哈希的拓展）避免冲突
  const Q = 1e4 + 7; const Q1 = 1e5 + 7; const Q2 = 1e6 + 7
  const f = [0]; const p = [1]
  const f1 = [0]; const p1 = [1]
  const f2 = [0]; const p2 = [1]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (s[i].charCodeAt(0) - 'a'.charCodeAt(0))) % Q
    p[i] = p[i - 1] * P % Q

    f1[i] = (f1[i - 1] * P % Q1 + (s[i].charCodeAt(0) - 'a'.charCodeAt(0))) % Q1
    p1[i] = p1[i - 1] * P % Q1

    f2[i] = (f2[i - 1] * P % Q2 + (s[i].charCodeAt(0) - 'a'.charCodeAt(0))) % Q2
    p2[i] = p2[i - 1] * P % Q2
  }
  const hash = (i, j) => {
    return ((f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q) &&
           ((f1[j] - f1[i - 1] * p1[j - i + 1] % Q1 + Q1) % Q1) &&
           ((f2[j] - f2[i - 1] * p2[j - i + 1] % Q2 + Q2) % Q2)
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
