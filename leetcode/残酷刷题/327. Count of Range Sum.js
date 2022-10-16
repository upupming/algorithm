/**
 * @param {number[]} nums
 * @param {number} lower
 * @param {number} upper
 * @return {number}
 */
 var countRangeSum = function(nums, lower, upper) {
  const sum = [0], n = nums.length
  for (let i = 0; i < n; i++) sum[i+1] = sum[i]+nums[i]
  let ans = 0

  const count = (i, j) => {
      if (i === j) return
      const t = i+j>>1
      count(i, t)
      count(t+1, j)
      for (let x = i; x <= t; x++) {
          let p = sum[x]+lower, q = sum[x]+upper
          // >=p 的第一个数
          let l = t+1, r = j+1
          while (l < r) {
              const mid = l+r>>1
              if (mid === j+1 || sum[mid] >= p) r = mid
              else l = mid+1
          }
          let p1 = l
          // <= q 的最后一个数
          l = t, r = j
          while (l < r) {
              const mid = l+r+1>>1
              if (mid === t || sum[mid] <= q) l = mid
              else r = mid-1
          }
          let p2 = l
          // console.log(sum, i, j, x, p1, p2)
          ans += p2-p1+1
      }

      let x = i, y = t+1, tmp = []
      while (x <= t && y <= j) {
          if (sum[x] <= sum[y]) tmp.push(sum[x++])
          else tmp.push(sum[y++])
      }
      while (x <= t) tmp.push(sum[x++])
      while (y <= j) tmp.push(sum[y++])
      for (let k = i; k <= j; k++) sum[k] = tmp[k-i]
  }
  count(0, n)

  return ans
};
