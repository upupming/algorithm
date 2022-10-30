/**
 * @param {number[]} nums
 * @return {number}
 */
const averageValue = function (nums) {
  let sum = 0; let cnt = 0
  for (const a of nums) {
    if (a % 2 === 0 && a % 3 === 0) sum += a, cnt += 1
  }
  if (cnt === 0) return 0
  return Math.floor(sum / cnt)
}
