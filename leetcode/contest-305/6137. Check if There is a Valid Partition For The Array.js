/**
 * @param {number[]} nums
 * @return {boolean}
 */
 var validPartition = function(nums) {
  const n = nums.length
  const dp = Array(n).fill(0)
  dp[-1] = 1
  for (let i = 0; i < n; i++) {
      if (i-1 >= 0 && nums[i] === nums[i-1]) {
          dp[i] ||= dp[i-2]
          if (i-2 >= 0 && nums[i-1] === nums[i-2]) {
              dp[i] ||= dp[i-3]
          }
      }
      if (i-2>=0 && nums[i] === nums[i-1]+1 && nums[i-1] === nums[i-2]+1) {
          dp[i] ||= dp[i-3]
      }
  }
  return Boolean(dp[n-1])
};
