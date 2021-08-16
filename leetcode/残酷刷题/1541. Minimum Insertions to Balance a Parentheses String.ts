function minInsertions (s: string): number {
  let ans = 0; let cnt = 0
  for (const ch of s) {
    if (ch === '(') {
      cnt += 2
      // 加个右括号
      if (cnt % 2 === 1) {
        cnt -= 1
        ans++
      }
    }
    else cnt -= 1
    if (cnt < 0) {
      cnt += 2
      ans++
    }
  }
  return ans + cnt
};
