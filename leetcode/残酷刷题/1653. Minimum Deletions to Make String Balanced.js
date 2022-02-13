/**
 * @param {string} s
 * @return {number}
 */
const minimumDeletions = function (s) {
  const n = s.length
  let a = 0; let b = 0
  for (let i = 0; i < n; i++) {
    if (s[i] === 'a') a++
    else b++
  }
  let a0 = 0; let b0 = 0
  let ans = 1e6
  for (let i = 0; i < n; i++) {
    if (s[i] === 'a') a0++
    else b0++
    const a1 = a - a0; const b1 = b - b0
    // console.log(i, a0, b0, a1, b1, a1+b0)
    ans = Math.min(ans, a1 + b0)
  }
  return ans
}
