/**
 * @param {number[]} nums
 * @param {number} modulo
 * @param {number} k
 * @return {number}
 */
var countInterestingSubarrays = function(nums, m, k) {
  // mp[余数] = 出现的次数
  let n = nums.length, mp = {}, r = 0, ans = 0
  mp[0] = 1
  for (let i = 0; i < n; i++) {
      // console.log(nums[i] % m === k, (nums[i] % m) === k)
      r = (r + (nums[i] % m === k)) % m
      let target = (r-k+m)%m
      ans += mp[target] ?? 0
      // console.log(i, nums[i], r, mp[r], ans)
      mp[r] ??=0, mp[r]++
  }
  return ans
};
