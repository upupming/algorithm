/**
 * @param {number[][]} points
 * @param {number} k
 * @return {number}
 */
const findMaxValueOfEquation = function (points, k) {
  const n = points.length
  const q = []; let ans = -1e10
  // xj-xi+yi+yj
  for (let i = 0, j = 0; i < n; i++) {
    while (j < n && points[j][0] - points[i][0] <= k) {
      while (q.length && q[q.length - 1][0] <= points[j][0] + points[j][1]) q.pop()
      q.push([points[j][0] + points[j][1], j])
      j++
    }
    while (q.length && q[0][1] <= i) q.shift()

    if (q.length) { ans = Math.max(ans, q[0][0] - points[i][0] + points[i][1]) }
  }
  return ans
}
