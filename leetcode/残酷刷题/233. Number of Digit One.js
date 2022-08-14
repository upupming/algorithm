/**
 * @param {number} n
 * @return {number}
 */
const countDigitOne = function (n) {
  const s = String(n)
  const m = s.length
  let ans = 0
  for (let i = 0; i < m; i++) {
    // left [bi] right
    const left = Number(s.slice(0, i)); const leftLen = i
    const bi = Number(s[i])
    const right = Number(s.slice(i + 1)); const rightLen = m - i - 1
    // [0~left-1] [1] [0~9...9(rightLen位)]
    const cnt1 = Math.pow(10, rightLen)
    ans += left * cnt1
    if (bi > 1) {
      // 0~9...9(rightLen位)
      ans += cnt1
    } else if (bi === 1) {
      // 0~right
      ans += right + 1
    }
  }
  return ans
}
