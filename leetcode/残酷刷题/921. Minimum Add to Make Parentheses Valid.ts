function minAddToMakeValid (s: string): number {
  let [cnt, ans] = [0, 0]
  for (let i = 0; i < s.length; i++) {
    if (s.charAt(i) === '(') cnt++
    else cnt--
    if (cnt < 0) {
      ans++
      cnt = 0
    }
  }
  return ans + cnt
};
