/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}

importance[i][j]
count[i][j]
 */
var minCost = function(nums, k) {
  const n = nums.length
  const ipt = Array(n).fill(0).map(() => Array(n))
  for (let i = 0; i < n; i++) {
      let cnt = Array(n).fill(0)
      let tmp = 0
      for (let j = i; j < n; j++) {
          if(++cnt[nums[j]] >= 2) {
              if (cnt[nums[j]] === 2) tmp += 2
              else tmp++
          }
          ipt[i][j] = tmp
      }
  }
  const dp = Array(n).fill(0)
  for (let i = 0; i < n; i++) {
      dp[i] = k+ipt[0][i]
      for (let j = 0; j < i; j++) {
          dp[i] = Math.min(
              dp[i],
              dp[j] + k+ipt[j+1][i]
          )
      }
  }
  return dp[n-1]
};
