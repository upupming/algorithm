/**
 * @param {number[]} nums
 * @return {number}
 */
 var sumOfBeauties = function(nums) {
  let l = [], r = [], n = nums.length
  l[0] = nums[0], r[n-1] = nums[n-1]
  for (let i = 1; i < n; i++) l[i] = Math.max(l[i-1], nums[i])
  for (let i = n-2; i >= 0; i--) r[i] = Math.min(r[i+1], nums[i])
  let ans = 0
  for (let i = 1; i <= n-2; i++) {
      if (nums[i] > l[i-1] && nums[i] < r[i+1]) ans += 2
      else if (nums[i] > nums[i-1] && nums[i] < nums[i+1]) ans += 1
  }
  return ans
};