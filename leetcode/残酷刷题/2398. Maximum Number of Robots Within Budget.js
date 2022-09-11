/**
 * @param {number[]} chargeTimes
 * @param {number[]} runningCosts
 * @param {number} budget
 * @return {number}
 */
const maximumRobots = function (c, r, b) {
  const n = c.length; const q = []
  let ans = 0
  for (let i = 0, j = 0, sum = 0; i < n; i++) {
    // [i, j)
    while (j < n) {
      if (j >= i) {
        // 如果加上 j 会出问题，就停止
        const max = Math.max(c[j], q.length ? c[q[0]] : 0)
        if (max + (j - i + 1) * (sum + r[j]) > b) break

        while (q.length && c[q[q.length - 1]] <= c[j]) q.pop()
        q.push(j)
      }
      sum += r[j]

      j++
    }
    // console.log(i, j, sum, q[0], q.length ? c[q[0]] : 0)
    ans = Math.max(ans, j - i)

    while (q.length && q[0] <= i) q.shift()
    sum -= r[i]
  }
  return ans
}
