/**
 * @param {number[]} nums
 * @return {number}

3, 1, 2 => 11, 01, 10
4, 3, 1, 2, 4 => 100, 11, 01, 10, 100
满足条件的子数组：每一位上 1 出现的次数为偶数次，异或结果为 0
异或结果 <= 10^6，因此可以存储下 map[异或结果] = 前面的出现次数
 */
var beautifulSubarrays = function(nums) {
  let mp = {}, n = nums.length, xor = 0, ans = 0
  mp[0] = 1
  for (let i = 0; i < n; i++) {
      xor ^= nums[i]
      ans += mp[xor] ?? 0
      mp[xor] ??= 0
      mp[xor]++
  }
  return ans
};
