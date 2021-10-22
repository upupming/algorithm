/**
 * @param {number[]} nums
 * @param {number} goal
 * @return {number}
 */
 var minAbsDifference = function(nums, goal) {
  // 双向搜索: 2^20 的时间复杂度是刚好的
  // 分成两半，先看左边构成的所有可能的和，在右边找一个能够让其最接近 goal 的数，可以用二分来求解
  const n = nums.length
  const nl = Math.floor(nums.length / 2)
  const left = [], right = []
  subArray(nums.slice(0, nl), left)
  subArray(nums.slice(nl), right)
  let ans = 1e10
  left.forEach(x => {
      const y = goal - x
      // 在 right 中找最接近 y 的元素
      // >= y 的最小元素
      let l = 0, r = right.length - 1
      while (l < r) {
          const mid = l + r >> 1
          if (right[mid] >= y) r = mid
          else l = mid + 1
      }
      ans = Math.min(ans, Math.abs(y - right[l]))
      // <= y 的最大元素
      l = 0, r = right.length - 1
      while (l < r) {
          const mid = (l + r + 1) >> 1
          if (right[mid] <= y) l = mid
          else r = mid - 1
      }
      ans = Math.min(ans, Math.abs(y - right[l]))
  })
  return ans

  function subArray(arr, subArr) {
      const m = arr.length
      for (let i = 0; i < 1 << m; i++) {
          let sum = 0
          for (let j = 0; j < m; j++) {
              if (i >> j & 1) {
                  sum += arr[j]
              }
          }
          subArr.push(sum)
      }
      subArr.sort((a, b) => a - b)
  }
};
