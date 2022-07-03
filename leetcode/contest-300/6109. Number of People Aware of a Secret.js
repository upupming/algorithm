/**
 * @param {number} n
 * @param {number} delay
 * @param {number} forget
 * @return {number}
 */
const peopleAwareOfSecret = function (n, d, f) {
  const a = [[1, 0]]; let ans = 1; const P = 1e9 + 7
  for (let i = 1; i < n; i++) {
    while (a.length && i - a[0][1] >= f) ans = (ans - a[0][0] + P) % P, a.shift()
    let j = a.length - 1
    while (j >= 0 && a[j][1] > i - d) j--
    let tmp = 0
    for (let k = j; k >= 0; k--) tmp = (tmp + a[k][0]) % P
    // console.log(i, a, ans)
    a.push([tmp, i]), ans = (ans + tmp) % P
  }
  return ans
}
