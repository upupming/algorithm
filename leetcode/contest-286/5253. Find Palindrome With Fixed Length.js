/**
 * @param {number[]} queries
 * @param {number} intLength
 * @return {number[]}
 */
const kthPalindrome = function (q, l) {
  let n
  if (l % 2) n = (l - 1) / 2
  else n = l / 2
  // 特殊

  const all = []; let m
  if (l === 1) { m = 9 } else {
    m = Math.pow(10, n) - Math.pow(10, n - 1)
    if (l % 2) m *= 10
  }

  const get = (y) => {
    if (l === 1) return y
    let i, j
    if (l % 2) {
      i = Math.pow(10, n - 1) + Math.ceil(y / 10) - 1
      j = (y % 10 - 1 + 10) % 10
    } else {
      i = Math.pow(10, n - 1) + y - 1
    }
    // console.log(y, i, j)
    const left = i.toString()
    const right = left.split('').reverse().join('')
    if (l % 2) {
      return Number(left + j + right)
    } else {
      return Number(left + right)
    }
  }
  const ans = []
  for (const x of q) {
    if (x > m) ans.push(-1)
    else ans.push(get(x))
  }
  return ans
}
