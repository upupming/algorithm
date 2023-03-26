/**
 * @param {number[]} nums
 * @return {boolean}
 */
const primeSubOperation = function (nums) {
  const v = Array(1e3 + 1).fill(0); const p = []
  for (let i = 2; i <= 1e3; i++) {
    if (v[i]) continue
    p.push(i)
    for (let j = i; j <= 1e3 / i; j++) v[i * j] = 1
  }
  for (let i = nums.length - 2; i >= 0; i--) {
    if (nums[i] >= nums[i + 1]) {
      let j = 0
      for (; j <= p.length - 1; j++) {
        if (nums[i] > p[j] && nums[i] - p[j] < nums[i + 1]) break
        // console.log(nums[i], p[j])
      }
      if (j <= p.length - 1 && nums[i] - p[j] < nums[i + 1] && nums[i] - p[j] > 0) nums[i] -= p[j]
      else {
        // console.log(i, nums[i], nums.slice(i+1), j, p[j])
        return false
      }
    }
  }
  return true
}
