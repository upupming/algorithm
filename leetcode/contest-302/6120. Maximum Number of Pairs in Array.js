/**
 * @param {number[]} nums
 * @return {number[]}
 */
const numberOfPairs = function (nums) {
  const cnt = {}
  for (const a of nums) {
    cnt[a] ??= 0
    cnt[a]++
  }
  let p = 0; let l = 0
  for (const [k, v] of Object.entries(cnt)) {
    p += Math.floor(v / 2)
    l += v % 2
  }
  return [p, l]
}
