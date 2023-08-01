/**
 * @param {number[]} nums
 * @return {number}
 */
var countQuadruplets = function(nums) {
  const n = nums.length
  let ans = 0

  const prev = Array(n+1).fill(0).map(() => Array(n+1).fill(0))
  const post = Array(n+1).fill(0).map(() => Array(n+1).fill(0))
  for (let i = 0; i < n; i++) {
      // 数的范围只能是 1~n
      for (let j = 1; j <= n; j++) {
          if (nums[i] < j) prev[i][j] = (i<=0 ? 0 : prev[i-1][j])+1
          else prev[i][j] = i<=0 ? 0 : prev[i-1][j]
      }
      let k = n-1-i
      for (let j = 1; j <= n; j++) {
          if (nums[k] > j) post[k][j] = post[k+1][j]+1
          else post[k][j] = post[k+1][j]
          // console.log(k, j, post[k][j])
      }
  }

  for (let j = 0; j < n; j++) {
      for (let k = j+1; k < n; k++) {
          if (nums[k] < nums[j]) {
              let l = j-1<0 ? 0 : prev[j-1][nums[k]]
              let r = post[k+1][nums[j]]
              // post[3][5]
              // console.log(j, k, nums[j], nums[k], l, r)
              ans += l*r
          }
      }
  }
  return ans
};
