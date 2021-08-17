function checkValidString (s: string): boolean {
  let [cntMin, cntMax] = [0, 0]
  for (const ch of s) {
    if (ch === '(') {
      cntMin++
      cntMax++
    } else if (ch === ')') {
      cntMin--
      cntMax--
    } else {
      cntMax++
      cntMin--
    }
    if (cntMax < 0) return false
    if (cntMin < 0) cntMin = 0
  }
  return cntMin === 0
};
