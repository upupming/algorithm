/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
 var targetIndices = function(nums, target) {
  nums.sort((a, b) => a - b)
  let ans = []
  for (let i = 0; i < nums.length; i++) {
      if (nums[i] === target) ans.push(i)
  }
  return ans
};
