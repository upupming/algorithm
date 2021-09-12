/**
 * @param {string} s
 * @return {number}
 */
const maxProduct = function (s) {
  const n = s.length
  const isP = (s) => s === s.split('').reverse().join('')
  const get = (i) => {
    let t = ''
    for (let k = 0; k < n; k++) if (i >> k & 1) t += s[k]
    return t
  }
  let ans = 0
  for (let i = 1; i < 1 << n; i++) {
    const si = get(i)
    if (!isP(si)) continue
    for (let j = i + 1; j < 1 << n; j++) {
      if ((j & i) > 0) continue
      const sj = get(j)
      if (isP(sj)) ans = Math.max(ans, si.length * sj.length)
    }
  }
  return ans
}
