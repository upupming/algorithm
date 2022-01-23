/**
 * @param {number[]} nums
 * @return {number[]}
 */
 var rearrangeArray = function(nums) {
  let p = [], n = [], ans = []
  for (const x of nums) {
      if (x > 0) p.push(x)
      else n.push(x)
  }
  for (let i = 0; i < p.length; i++) {
      ans.push(p[i])
      ans.push(n[i])
  }
  return ans
};
