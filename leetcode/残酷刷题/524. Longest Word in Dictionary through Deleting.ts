function findLongestWord (s: string, dictionary: string[]): string {
  const idx: number[][] = [...Array(26)].map(() => [])
  for (let i = 0; i < s.length; i++) {
    idx[s.charCodeAt(i) - 'a'.charCodeAt(0)].push(i)
  }

  dictionary.sort((a, b) => {
    if (a.length === b.length) {
      return a.localeCompare(b)
    }
    return -(a.length - b.length)
  })
  for (const d of dictionary) {
    if (isSub(s, d)) return d
  }
  return ''
  function isSub (s: string, t: string): boolean {
    let j = 0
    for (let i = 0; i < s.length && j < t.length; j++) {
      const ch = t.charCodeAt(j) - 'a'.charCodeAt(0)
      if (!idx[ch].length) return false
      let [l, r] = [0, idx[ch].length - 1]
      // >= i 的第一个地方
      while (l < r) {
        const mid = (l + r) >> 1
        if (idx[ch][mid] >= i) r = mid
        else l = mid + 1
      }
      // console.log(i, j, l, idx[ch][l])
      if (idx[ch][l] >= i) i = idx[ch][l] + 1
      else return false
    }
    // console.log(j, t)
    return j === t.length
  }
};
