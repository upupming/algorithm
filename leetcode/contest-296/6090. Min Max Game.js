/**
 * @param {number[]} nums
 * @return {number}
 */
 var minMaxGame = function(nums) {
  if (nums.length <= 1) return nums
  let a = []
  for (let i = 0; i < nums.length; i+=2) {
      if (i / 2 % 2 === 1) {
          a.push(Math.max(nums[i], nums[i+1]))
      } else {
          a.push(Math.min(nums[i], nums[i+1]))
      }
  }
  return minMaxGame(a)
};
