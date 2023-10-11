/**
 * @param {number[]} nums
 * @param {number} p
 * @return {number}
 */
var minSubarray = function(nums, p) {
  // mp[余数] = 最往后的 index
  // 由于元素最多 10^5，最多有 10^5 种余数
  let mp = {}, n = nums.length, r = 0, ans = 1e10
  mp[0] = -1
  let sr = nums.reduce((prev, cur) => (prev+cur)%p, 0)
  if (sr === 0) return 0
  for (let i = 0; i < n; i++) {
      r = (r + nums[i]) % p
      // 区间的余数必须是 sr，和整体总余数相同，因此起点余数是 dr
      let dr = (r - sr + p) % p
      if (mp[dr] != null) {
          ans = Math.min(ans, i - mp[dr])
      }
      mp[r] = i
  }
  return ans >= n ? -1 : ans
};
