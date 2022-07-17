/**
 * @param {number[]} nums
 * @return {number}
 */
const maximumSum = function (nums) {
  const map = {}
  for (const x of nums) {
    let s = 0; let y = x
    while (y) {
      s += y % 10
      y = Math.floor(y / 10)
    }
    map[s] ??= []
    map[s].push(x)
  }
  let ans = -1
  for (const [k, v] of Object.entries(map)) {
    if (v.length < 2) continue
    v.sort((a, b) => (b - a))
    ans = Math.max(ans, v[0] + v[1])
  }
  return ans
}
