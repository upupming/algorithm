/**
 * @param {number[]} plants
 * @param {number} capacity
 * @return {number}
 */
const wateringPlants = function (p, c) {
  const n = p.length
  let r = c; let ans = 0
  for (let i = 0; i < n; i++) {
    if (r >= p[i]) {
      r -= p[i]
      ans += 1
    } else {
      ans += 2 * i + 1
      r = c - p[i]
    }
  }
  return ans
}
