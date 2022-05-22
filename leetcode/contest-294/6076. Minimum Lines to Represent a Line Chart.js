/**
 * @param {number[][]} stockPrices
 * @return {number}
 */
const minimumLines = function (s) {
  const n = s.length
  s.sort((a, b) => a[0] - b[0])
  let ans = 0
  for (let i = 0; i < n;) {
    if (i === n - 1) {
      break
    } else {
      const p = [s[i + 1][0] - s[i][0], s[i + 1][1] - s[i][1]]; let j = i + 2
      while (j < n && (BigInt(p[0]) * BigInt(s[j][1] - s[i][1])) === (BigInt(p[1]) * BigInt(s[j][0] - s[i][0]))) {
        j++
      }
      ans++
      // console.log(i, p, j-1)
      i = j - 1
    }
  }
  return ans
}
