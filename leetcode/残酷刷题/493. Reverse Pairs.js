/**
 * @param {number[]} nums
 * @return {number}
 */
const reversePairs = function (nums) {
  const n = nums.length
  let ans = 0
  const count = (i, j) => {
    if (i === j) return
    const t = i + j >> 1
    count(i, t)
    count(t + 1, j)
    for (let x = i; x <= t; x++) {
      const q = nums[x] / 2
      // < q 的最后一个数
      l = t, r = j
      while (l < r) {
        const mid = l + r + 1 >> 1
        if (mid === t || nums[mid] < q) l = mid
        else r = mid - 1
      }
      ans += l - t
    }

    let x = i; let y = t + 1; const tmp = []
    while (x <= t && y <= j) {
      if (nums[x] <= nums[y]) tmp.push(nums[x++])
      else tmp.push(nums[y++])
    }
    while (x <= t) tmp.push(nums[x++])
    while (y <= j) tmp.push(nums[y++])
    for (let k = i; k <= j; k++) nums[k] = tmp[k - i]
  }
  count(0, n - 1)
  return ans
}
