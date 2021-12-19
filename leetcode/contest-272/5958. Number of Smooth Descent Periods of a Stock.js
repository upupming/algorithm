/**
 * @param {number[]} prices
 * @return {number}
 */
const getDescentPeriods = function (p) {
  const n = p.length
  let ans = 0
  for (let i = 0; i < p.length; i++) {
    let j = i
    while (j + 1 < n && p[j + 1] === p[j] - 1) j++
    const len = j - i + 1
    ans += len * (len + 1) / 2
    i = j
  }
  return ans
}
