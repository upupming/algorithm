/**
 * @param {number[]} grades
 * @return {number}
 */
const maximumGroups = function (g) {
  const n = g.length
  let l = 1; let r = n
  const valid = (k) => (1 + k) * k <= 2 * n
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }
  return l
}
