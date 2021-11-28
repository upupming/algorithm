/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
 var getAverages = function(nums, k) {
  const n = nums.length, sum = [0]
  for (let i = 1; i <= n; i++) {
      sum[i] = sum[i-1] + nums[i-1]
  }
  const ans = []
  for (let i = 1; i <= n; i++) {
      const l = i - k, r = i + k
      if (l < 1 || r > n) ans.push(-1)
      else {
          ans.push(Math.floor((sum[r] - sum[l-1]) / (r - l + 1)))
      }
  }
  return ans
};
