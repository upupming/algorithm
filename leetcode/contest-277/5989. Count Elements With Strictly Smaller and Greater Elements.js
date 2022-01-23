/**
 * @param {number[]} nums
 * @return {number}
 */
 var countElements = function(nums) {
  let min = 1e5+10, max = -min
  for (const x of nums) {
      min = Math.min(min, x)
      max = Math.max(max, x)
  }
  let ans = 0
  for (const x of nums) {
      if (x !== min && x !== max) ans++
  }
  return ans
};
