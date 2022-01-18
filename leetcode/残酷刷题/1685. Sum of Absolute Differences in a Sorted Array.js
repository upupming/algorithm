/**
 * @param {number[]} nums
 * @return {number[]}
 */
 var getSumAbsoluteDifferences = function(nums) {
  const sum = [], n = nums.length
  sum[-1] = 0
  for (let i = 0; i < n; i++) sum[i] = nums[i] + sum[i-1]
  const ans = []
  for (let i = 0; i < n; i++) {
      ans[i] = (i * nums[i] - sum[i-1]) + ((sum[n-1] - sum[i]) - (n-i-1) * nums[i])
  }
  return ans
};
