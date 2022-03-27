/**
 * @param {number[]} nums
 * @return {number}
 */
 var minDeletion = function(nums) {
  const n = nums.length
  let d = 0, k = -1
  for (let i = 0, l = -1; i < n; i++) {
      if (l != -1 && nums[i] === nums[l] && (k % 2 === 0)) {
          d++
      } else {
          l = i
          k++
      }
  }
  if ((n - d) % 2) d++
  return d
};
