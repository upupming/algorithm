/**
 * @param {string[]} bank
 * @return {number}
 */
 var numberOfBeams = function(bank) {
  let last = 0, ans = 0
  bank.forEach(row => {
      const cnt = row.split('').reduce((p, c) => p + (c === '1'), 0)
      // console.log(row, cnt, last)
      if (cnt > 0) {
          ans += last * cnt
          last = cnt
      }
  })
  return ans
};
