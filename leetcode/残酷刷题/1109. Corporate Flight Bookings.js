/**
 * @param {number[][]} bookings
 * @param {number} n
 * @return {number[]}
 */
const corpFlightBookings = function (bookings, n) {
  const diff = Array(n + 1).fill(0)
  for (const [f, l, s] of bookings) {
    diff[f] += s
    diff[l + 1] -= s
  }
  const ans = []
  for (let i = 1; i <= n; i++) {
    diff[i] += diff[i - 1]
    ans.push(diff[i])
  }
  return ans
}
