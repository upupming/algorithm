/**
 * @param {string} s
 * @return {string}
 */
const longestDupSubstring = function (s) {
  const n = s.length
  s = ' ' + s

  const P = 131n
  // 这题数据有点强，被迫用较大的 Q (1 << 64 等价于 unsigned long long 的取余特性)
  const Q = 1n << 64n
  const f = [0n]; const p = [1n]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q
    p[i] = p[i - 1] * P % Q
  }
  // console.log(f, p)

  const hash = (i, j) => {
    // 乘完之后的取模非常重要，漏掉就会 WA（出现较小负数导致 + 一个 Q 不够）
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }
  const len2Idx = {}
  let l = 1; let r = n
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }
  if (valid(l)) return s.slice(len2Idx[l], len2Idx[l] + l)
  return ''

  function valid (mid) {
    const set = new Set()
    // 滑窗 [i, i+mid-1]
    for (let i = 1; i + mid - 1 <= n; i++) {
      const j = i + mid - 1
      const h = hash(i, j)
      if (set.has(h)) {
        len2Idx[mid] = i
        return true
      }
      set.add(h)
    }
    return false
  }
}
