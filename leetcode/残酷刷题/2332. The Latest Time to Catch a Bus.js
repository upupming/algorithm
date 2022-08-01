/**
 * @param {number[]} buses
 * @param {number[]} passengers
 * @param {number} capacity
 * @return {number}
 */
const latestTimeCatchTheBus = function (bs, ps, cs) {
  bs.sort((a, b) => a - b)
  ps.sort((a, b) => a - b)
  const n = bs.length; const m = ps.length
  let ans = 0
  for (let i = 0, j = 0; i < n; i++) {
    let c = cs
    while (c && j < m && ps[j] <= bs[i]) {
      if (j === 0 || ps[j - 1] < ps[j] - 1) {
        ans = Math.max(ans, ps[j] - 1)
      }
      j++
      c--
    }

    if (c > 0) {
      // 在公交车到的时候上车
      if (j === 0 || (j >= 1 && ps[j - 1] < bs[i])) {
        ans = Math.max(ans, bs[i])
      }
    }
  }
  return ans
}
