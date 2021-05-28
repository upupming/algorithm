/*
 * @lc app=leetcode id=1870 lang=typescript
 *
 * [1870] Minimum Speed to Arrive on Time
 * 裸的二分
 */

// @lc code=start
function minSpeedOnTime (dist: number[], hour: number): number {
  let [l, r] = [1, 1e7]
  const valid = (speed: number): boolean => {
    let total = 0
    for (let i = 0; i < dist.length - 1; i++) {
      total += Math.ceil(dist[i] / speed)
    }
    total += dist[dist.length - 1] / speed
    return total <= hour
  }
  if (!valid(r)) return -1
  while (l < r) {
    const mid = (l + r) >> 1
    if (valid(mid)) r = mid
    else l = mid + 1
  }
  return l
};
// @lc code=end
