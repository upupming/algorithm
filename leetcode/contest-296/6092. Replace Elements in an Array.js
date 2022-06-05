/**
 * @param {number[]} nums
 * @param {number[][]} operations
 * @return {number[]}
 */
 var arrayChange = function(nums, operations) {
  const cnt = {}
  for (let i = 0; i < nums.length; i++) {
      cnt[nums[i]] = [i]
  }
  console.log(cnt)
  for (const [x, y] of operations) {
      cnt[y] = cnt[x]
      delete cnt[x]
  }
  // console.log(cnt)
  let ans = []
  for (const [k, v] of Object.entries(cnt)) {
      for (const idx of v) ans[idx] = Number(k)
  }
  return ans
};
