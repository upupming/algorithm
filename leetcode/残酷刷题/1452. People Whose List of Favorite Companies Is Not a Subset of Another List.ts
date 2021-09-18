function peopleIndexes (favoriteCompanies: string[][]): number[] {
  let [s, m] = [new Map<string, number>(), 0]
  favoriteCompanies.forEach(f => f.forEach(c =>
    s.has(c) ? null : s.set(c, m++)))
  const b = favoriteCompanies.map(f => f.reduce((p, c) => p + (1 << s.get(c)!), 0))
  let ans = []
  for (let i = 0; i < b.length; i++) {
    let ok = true
    for (let j = 0; j < b.length; j++) {
      if (j === i) continue
      if ((b[i] & b[j]) === b[i]) {
        ok = false
        break
      }
    }
    if (ok) ans.push(i)
  }
  return ans
};
