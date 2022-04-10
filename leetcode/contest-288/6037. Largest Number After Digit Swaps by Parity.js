/**
 * @param {number} num
 * @return {number}
 */
 var largestInteger = function(num) {
  const d = String(num).split('').map(Number)
  const x = [...d].sort((a, b) => -(a-b))
  const odd = [...x].filter(x => x % 2 === 1)
  const even = [...x].filter(x => x % 2 === 0)
  let ans = ''
  for (let i = 0, j = 0, k = 0; i < d.length; i++) {
      if (d[i] % 2 === 1) {
          ans += odd[j++]
      } else ans += even[k++]
  }
  return ans
};
