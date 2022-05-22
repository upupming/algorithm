/**
 * @param {number[]} capacity
 * @param {number[]} rocks
 * @param {number} additionalRocks
 * @return {number}
 */
const maximumBags = function (c, r, a) {
  const x = []
  const n = c.length
  for (let i = 0; i < n; i++) {
    x.push(c[i] - r[i])
  }
  x.sort((a, b) => a - b)
  let cnt = 0
  for (const y of x) {
    if (a < y) break
    a -= y
    cnt++
  }
  return cnt
}
