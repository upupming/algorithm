/**
 * @param {number[]} candies
 * @param {number} k
 * @return {number}
 */
const maximumCandies = function (c, k) {
  let l = 0; let r = 1e7

  const valid = (x) => {
    let cnt = 0
    for (const y of c) {
      cnt += Math.floor(y / x)
    }
    return cnt >= k
  }

  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }

  return l
}
