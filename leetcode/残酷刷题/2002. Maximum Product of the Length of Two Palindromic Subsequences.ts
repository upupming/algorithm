function maxProduct (s: string): number {
  const n = s.length
  const isP = (s: string) => s.split('').reverse().join('') === s
  const getSub = (i: number) => {
    let u = ''
    for (let k = 0; k < n; k++) {
      if (i >> k & 1) u += s[k]
    }
    return u
  }
  let ans = 0
  for (let i = 0; i < 1 << n; i++) {
    const u = getSub(i)
    if (!isP(u)) continue
    const j = (1 << n) - 1 - i
    for (let l = j; l; l = (l - 1) & j) {
      const v = getSub(l)
      if (isP(v)) ans = Math.max(ans, u.length * v.length)
    }
  }
  return ans
};
