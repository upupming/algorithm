/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
 var partitionArray = function(nums, k) {
  nums.sort((a, b) => a - b)
  const n = nums.length
  let ans = 0
  for (let i = 0; i < nums.length; ) {
      let j = i
      while (j < n && nums[j] - nums[i] <= k) j++
      i = j, ans++
  }
  return ans
};
