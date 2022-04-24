/**
 * @param {number[][]} nums
 * @return {number[]}
 */
 var intersection = function(nums) {
  const cnt = {}
  for (const p of nums) {
      for (const a of p) cnt[a] = (cnt[a]||0)+1
  }
  let ans = []
  for (const [k, v] of Object.entries(cnt)) {
      if (v === nums.length) ans.push(Number(k))
  }
  return ans.sort((a, b) => a - b)
};
