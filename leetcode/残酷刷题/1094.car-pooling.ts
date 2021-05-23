/*
 * @lc app=leetcode id=1094 lang=typescript
 *
 * [1094] Car Pooling
 */

// @lc code=start
function carPooling (trips: number[][], capacity: number): boolean {
  let ans = 0
  for (let i = 0; i <= 1000; i++) {
    let tmp = 0
    for (const trip of trips) {
      if (trip[1] <= i && trip[2] > i) tmp += trip[0]
    }
    ans = Math.max(ans, tmp)
  }
  return ans <= capacity
};
// @lc code=end
