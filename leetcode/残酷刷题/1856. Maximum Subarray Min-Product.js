/**
 * @param {number[]} nums
 * @return {number}
 */
const maxSumMinProduct = function (nums) {
  const n = nums.length
  let ans = 0; const sum = []; let s = [-1]; const l = []; const r = []
  sum[-1] = 0, nums[-1] = nums[n] = -1
  for (let i = 0; i < n; i++) {
    sum[i] = sum[i - 1] + nums[i]
    while (nums[s[s.length - 1]] >= nums[i]) s.pop()
    l[i] = s[s.length - 1]
    s.push(i)
  }
  s = [n]
  for (let i = n - 1; i >= 0; i--) {
    while (nums[s[s.length - 1]] >= nums[i]) s.pop()
    r[i] = s[s.length - 1]
    s.push(i)
  }
  for (let i = 0; i < n; i++) {
    // 区间和 [l[i]+1, r[i]-1]
    const tmp = BigInt(nums[i]) * BigInt(sum[r[i] - 1] - sum[l[i]])
    if (tmp > ans) ans = tmp
  }
  return ans % BigInt(1e9 + 7)
}
