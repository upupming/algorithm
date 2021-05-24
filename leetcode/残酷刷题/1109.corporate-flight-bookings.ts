/*
 * @lc app=leetcode id=1109 lang=typescript
 *
 * [1109] Corporate Flight Bookings
 */

// @lc code=start
function corpFlightBookings (bookings: number[][], n: number): number[] {
  const diff: number[] = Array(n + 1).fill(0); const ans: number[] = Array(n + 1).fill(0)
  for (const booking of bookings) {
    diff[booking[0]] += booking[2]
    diff[booking[1] + 1] -= booking[2]
  }
  for (let i = 1; i <= n; i++) {
    ans[i] = ans[i - 1] + diff[i]
  }
  ans.shift()
  return ans
};
// @lc code=end
