/**
 * @param {number[]} nums
 * @param {number[]} queries
 * @return {number[]}
 */
const minOperations = function (nums, q) {
  nums.sort((a, b) => a - b)
  const n = nums.length; const s = [0]
  for (let i = 0; i < n; i++) s[i + 1] = s[i] + nums[i]
  return q.map((qi) => {
    let l = 0; let r = n - 1
    while (l < r) {
      const mid = l + r >> 1
      if (nums[mid] >= qi) r = mid
      else l = mid + 1
    }
    // all less then qi
    if (nums[l] < qi) return qi * n - s[n]
    else {
      return qi * l - s[l] + s[n] - s[l] - qi * (n - l)
    }
  })
}

// console.log(minOperations([3, 1, 6, 8],
//   [1, 5]))
// console.log(minOperations([2, 9, 6, 3], [10]))
