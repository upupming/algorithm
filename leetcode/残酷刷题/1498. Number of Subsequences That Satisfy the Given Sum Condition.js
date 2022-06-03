/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
 var numSubseq = function(nums, target) {
  const n = nums.length, P = 1e9+7
  nums.sort((a, b) => a-b)
  let ans = 0
  for (let i = 0, j = n-1; i < n; i++) {
      while (j > i && nums[i] + nums[j] > target) j--
      if (j < i || nums[i] + nums[j] > target) break
      ans = (ans + Number(2n ** BigInt(j-i) % BigInt(P))) % P
  }
  return ans
};
