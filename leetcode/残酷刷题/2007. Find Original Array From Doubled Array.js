/**
 * @param {number[]} changed
 * @return {number[]}
 */
const findOriginalArray = function (changed) {
  if (changed.length % 2 !== 0) return []
  const cnt = {}
  for (const val of changed) {
    cnt[val] ??= 0
    cnt[val]++
  }
  const a = Object.keys(cnt).sort((a, b) => b - a)
  const ans = []
  for (const val of a) {
    while (cnt[val]) {
      const half = val / 2
      if (val % 2 !== 0 || !cnt[half]) return []
      cnt[val]--, cnt[half]--
      ans.push(half)
    }
  }
  return ans
}
