/**
 * @param {number} numArrows
 * @param {number[]} aliceArrows
 * @return {number[]}
 */
const maximumBobPoints = function (n, a) {
  let ans = 0; let arr
  const m = a.length
  for (let i = 0; i < 1 << m; i++) {
    let d = 0; const tmp = Array(m).fill(0); let s = 0
    for (let j = 0; j < m; j++) {
      if (i >> j & 1) {
        d += j
        s += tmp[j] = a[j] + 1
      }
    }
    if (s <= n) {
      if (ans < d) {
        ans = d
        tmp[0] += n - s
        arr = tmp
      }
    }
  }
  // console.log(ans)
  // console.log(arr.reduce((p, c) => p+c, 0))
  return arr
}
