/**
 * @param {number[]} nums
 * @return {number[]}
 */
const findLonely = function (nums) {
  const cnt = {}
  for (const x of nums) {
    cnt[x] ??= 0
    cnt[x]++
  }
  const ans = []
  for (const x of nums) {
    if (cnt[x] === 1 && !cnt[x - 1] && !cnt[x + 1]) ans.push(x)
  }
  return ans
}
