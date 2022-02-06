/**
 * @param {number} num
 * @return {number}
 */
 var smallestNumber = function(num) {
  const minus = num < 0
  const s = String(Math.abs(num))
  const digits = s.split('').sort()
  if (minus) {
      return Number(-digits.sort((a, b) => -(a - b)).join(''))
  } else {
      // 最小的非 0 的字母
      if (digits.length === 1) return Number(digits.join(''))
      let min = '9', idx = -1
      for (let i = 0; i < digits.length; i++) {
          const d = digits[i]
          if (d <= min && d > '0') {
              min = d
              idx = i
          }
      }
      digits.splice(idx, 1)
      digits.sort()
      // console.log(min)
      return Number([min, ...digits].join(''))
  }
};
