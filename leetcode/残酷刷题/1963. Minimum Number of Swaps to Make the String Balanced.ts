function minSwaps (s: string): number {
  let cnt = 0; let ans = 0
  for (let i = 0, j = s.length - 1; i < j; i++) {
    if (s[i] === '[') cnt++
    else cnt--
    if (cnt < 0) {
      while (s[j] !== '[') j--
      ans++; j--; cnt = 1
    }
  }
  return ans
};
