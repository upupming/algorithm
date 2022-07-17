/**
 * @param {string[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
const smallestTrimmedNumbers = function (nums, qs) {
  const n = nums.length; const m = qs.length
  const l = nums[0].length
  const idx = Array(n).fill(0).map((_, idx) => idx)
  const ans = []
  for (const [k, trim] of qs) {
    idx.sort((i, j) => {
      const s = nums[i].slice(l - trim, l)
      const t = nums[j].slice(l - trim, l)
      if (s === t) return i - j
      return s < t ? -1 : 1
    })
    ans.push(idx[k - 1])
  }
  return ans
}
