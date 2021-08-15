function minRemoveToMakeValid (s: string): string {
  const idx = []
  let remove = []
  for (let i = 0; i < s.length; i++) {
    const ch = s[i]
    if (ch === '(') idx.push(i)
    else if (ch === ')') {
      if (idx.length) {
        idx.pop()
      } else {
        remove.push(i)
      }
    }
  }
  remove = remove.concat(idx)
  let ans = ''
  for (let i = 0, j = 0; i < s.length; i++) {
    while (j < remove.length && remove[j] < i) j++
    if (j < remove.length && remove[j] === i) continue
    ans += s[i]
  }
  return ans
};
