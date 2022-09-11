/**
 * @param {number[]} nums
 * @return {number}
 */
const mostFrequentEven = function (nums) {
  const cnt = {}
  for (const x of nums) {
    cnt[x] ??= 0
    cnt[x]++
  }
  const ans = Object.entries(cnt).filter(x => x[0] % 2 === 0).sort((a, b) => {
    if (a[1] === b[1]) return Number(a[0]) - Number(b[0])
    return b[1] - a[1]
  })
  return ans[0]?.[0] ?? -1
}
