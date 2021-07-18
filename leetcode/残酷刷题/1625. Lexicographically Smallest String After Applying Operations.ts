function findLexSmallestString (s: string, a: number, b: number): string {
  let ans = s
  // 偶数位
  for (let i = 0; i < 10; i++) {
    // 奇数位
    for (let j = 0; j < 10; j++) {
      let t = s.split('').map(ch => ch.charCodeAt(0) - '0'.charCodeAt(0))
      // 只有 b 为奇数时，才有可能让偶数位也可以加
      if (b % 2 === 1) {
        for (let l = 0; l < s.length; l += 2) {
          t[l] += a * i
          t[l] %= 10
        }
      }
      for (let l = 1; l < s.length; l += 2) {
        t[l] += a * j
        t[l] %= 10
      }
      // 旋转 n 次
      for (let m = 0; m < s.length; m++) {
        t = t.slice(-b).concat(t.slice(0, -b))
        const tmp = t.join('')
        if (tmp < ans) {
          ans = tmp
        }
      }
    }
  }
  return ans
};
