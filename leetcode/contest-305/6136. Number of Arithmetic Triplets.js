/**
 * @param {number[]} nums
 * @param {number} diff
 * @return {number}
 */
 var arithmeticTriplets = function(nums, diff) {
  const n = nums.length
  let ans = 0
  for (let i = 0; i < n; i++) {
      for (let j = i+1; j < n; j++) {
          for (let k = j+1; k < n; k++) {
              if (nums[j]-nums[i] === diff && nums[k] - nums[j] === diff) ans++
          }
      }
  }
  return ans
};
