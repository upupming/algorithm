/**
 * @param {number[]} nums
 * @return {number[]}
 */
const countSmaller = function (nums) {
  const n = nums.length
  const ans = []; const sorted = nums.slice()

  const solve = (i, j) => {
    if (i === j) return ans[i] = 0

    const mid = i + j >> 1
    solve(i, mid)
    solve(mid + 1, j)
    for (let x = i; x <= mid; x++) {
      let l = mid + 1; let r = j
      // 找到 [mid+1, j] 中最后一个 < nums[x] 的元素
      while (l < r) {
        const m = l + r + 1 >> 1
        if (sorted[m] < nums[x]) l = m
        else r = m - 1
      }
      // 没有小于的
      if (l === mid + 1 && !(sorted[l] < nums[x])) {}
      //
      else {
        // console.log(i, j, x, l, mid, sorted, nums)
        ans[x] += l - mid
      }
    }

    // 归并过程
    let x = i; let y = mid + 1
    const tmp = []
    while (x <= mid && y <= j) {
      if (sorted[x] <= sorted[y]) tmp.push(sorted[x++])
      else tmp.push(sorted[y++])
    }
    while (x <= mid) tmp.push(sorted[x++])
    while (y <= j) tmp.push(sorted[y++])

    for (let k = i; k <= j; k++) sorted[k] = tmp[k - i]
  }

  solve(0, n - 1)
  return ans
}
