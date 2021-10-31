/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
const possiblyEquals = function (s1, s2) {
  const isDigit = (ch) => ch >= '0' && ch <= '9'
  const isAlpha = (ch) => ch >= 'a' && ch <= 'z'
  const ch2Num = (ch) => ch.charCodeAt(0) - '0'.charCodeAt(0)

  // f[i][j][k] 表示 s1 匹配到第 i 个字符（以 1 为下标），s2 匹配到第 j 个字符，且 s1 匹配源字符串的长度减去 s2 匹配源字符串的长度为 k，是否有可能
  const n = s1.length; const m = s2.length
  // JS 的数组还是太慢了，这里试了三维数组，试了三维嵌套的对象都不行，最后是二维的 set 通过了
  const f = {}
  const set = (i, j, k) => {
    f[i] ??= {}
    f[i][j] ??= new Set()
    f[i][j].add(k)
  }
  const get = (i, j, k) => {
    return f?.[i]?.[j]?.has(k)
  }
  set(0, 0, 0, true)
  for (let i = 0; i <= n; i++) {
    for (let j = 0; j <= m; j++) {
      for (let k = -1000; k <= 1000; k++) {
        if (get(i, j, k)) {
          if (i < n) {
            if (isAlpha(s1[i])) {
              // 字母和字母匹配，若两个字母一样且当前长度差距为 0 才能一同前进
              if (j < m && isAlpha(s2[j]) && k === 0 && s1[i] === s2[j]) set(i + 1, j + 1, k, true)
              // s1 的字母和 s2 数字匹配，长度不能超过数字描述的范围（s1 长度 <= s2 长度）
              else if (j && isDigit(s2[j - 1]) && k + 1 <= 0) set(i + 1, j, k + 1, true)
            } else {
              // 数字可以任意匹配，循环次数不会超过 3
              for (let l = i, delta = 0; l < n && isDigit(s1[l]); l++) {
                delta = delta * 10 + ch2Num(s1[l])
                if (k + delta > 1000) break
                set(l + 1, j, k + delta, true)
              }
            }
          }
          if (j < m) {
            if (isAlpha(s2[j])) {
              if (i < n && isAlpha(s1[i]) && k === 0 && s1[i] === s2[j]) set(i + 1, j + 1, k, true)
              // （s1 长度 >= s2 长度）, s2 的字母和 s1 的数字匹配
              else if (i && isDigit(s1[i - 1]) && k - 1 >= 0) set(i, j + 1, k - 1, true)
            } else {
              // 数字可以任意匹配，循环次数不会超过 3
              for (let l = j, delta = 0; l < m && isDigit(s2[l]); l++) {
                delta = delta * 10 + ch2Num(s2[l])
                if (k - delta < -1000) break
                set(i, l + 1, k - delta, true)
              }
            }
          }
        }
      }
    }
  }

  return !!get(n, m, 0)
}
