/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
const minDifference = function (nums, queries) {
  const n = nums.length
  const idx = Array(101).fill(0).map(() => [])
  for (let i = 0; i < n; i++) idx[nums[i]].push(i)
  const ans = []
  for (const [a, b] of queries) {
    let last = -1; let min = 1e10
    for (let i = 1; i <= 100; i++) {
      // idx[i] 是否有 1 个值在 [a, b] 之间
      let l = 0; let r = idx[i].length - 1; let x; let y
      while (l < r) {
        const mid = l + r >> 1
        if (idx[i][mid] >= a) r = mid
        else l = mid + 1
      }
      if (!(idx[i][l] >= a)) continue
      // else x = l
      // l = 0, r = idx[i].length - 1
      // while (l < r) {
      //   const mid = l + r + 1 >> 1
      //   if (idx[i][mid] <= b) l = mid
      //   else r = mid - 1
      // }
      // if (!(idx[i][l] <= b)) continue
      // else y = l
      // if (y - x + 1 >= 1) {
      if (idx[i][l] <= b) {
        if (last !== -1) min = Math.min(min, i - last)
        last = i
      }
    }
    ans.push(min === 1e10 ? -1 : min)
  }
  return ans
}
