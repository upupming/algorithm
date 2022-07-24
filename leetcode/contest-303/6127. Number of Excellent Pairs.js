/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const countExcellentPairs = function (nums, k) {
  nums = [...new Set(nums)]
  const cnt = (x) => {
    let ans = 0
    while (x) {
      ans += x % 2
      x = Math.floor(x / 2)
    }
    return ans
  }
  nums = nums.map(x => [x, cnt(x)]).sort((a, b) => {
    if (a[1] !== b[1]) return a[1] - b[1]
    return a[0] - b[0]
  })
  const n = nums.length
  const get = (i, j) => {
    const [xi] = nums[i]
    const [xj] = nums[j]
    const a = xi & xj
    const b = xi | xj
    return cnt(a) + cnt(b) >= k
  }
  let ans = 0
  for (let i = 0; i < n; i++) {
    let l = 0; let r = n - 1
    function valid (mid) {
      return get(i, mid)
    }
    while (l < r) {
      const mid = l + r >> 1
      if (valid(mid)) r = mid
      else l = mid + 1
    }
    // [l, n-1]
    if (valid(l)) ans += n - l
  }
  return ans
}
