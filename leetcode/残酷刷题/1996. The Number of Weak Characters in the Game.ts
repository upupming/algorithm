function numberOfWeakCharacters (properties: number[][]): number {
  properties.sort((a, b) => a[0] - b[0])
  const n = properties.length
  let max = 0
  let ans = 0
  for (let i = n - 1; i >= 0;) {
    const curX = properties[i][0]
    let j = i; const lastMax = max
    for (; j >= 0; j--) {
      const [x, y] = properties[j]
      if (x !== curX) break
      if (lastMax > y) ans++
      max = Math.max(max, properties[j][1])
    }
    i = j
  }
  return ans
};
