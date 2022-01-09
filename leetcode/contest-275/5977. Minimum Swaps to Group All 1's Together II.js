/**
 * @param {number[]} nums
 * @return {number}
 */
 var minSwaps = function(nums) {
  let sum = [], tot = 0
  sum[-1] = 0
  const n = nums.length
  for (let i = 0; i < n; i++) {
      sum[i] = sum[i-1] + (nums[i] === 1)
      tot += (nums[i] === 1)
  }
  // console.log(sum)
  let ans = n
  for (let i = 0; i < n; i++) {
      let j = i + tot - 1
      if (j < n) {
          let cnt = sum[j] - sum[i-1]
          // console.log(j, i, cnt)
          ans = Math.min(ans, tot - cnt)
      } else {
          let len = n - i, leftLen = tot - len
          let k = leftLen - 1
          let cnt = sum[n-1] - sum[i-1] + sum[k]

          // console.log(i, j, k, cnt)
          ans = Math.min(ans, tot - cnt)
      }
  }
  return ans
};
