/**
 * @param {number[]} nums
 * @return {number[]}
 */
const maxScoreIndices = function (nums) {
  const n = nums.length
  const cnt0 = [0]; const cnt1 = [0]; const score = []
  for (let i = 1; i <= n; i++) {
    cnt0[i] = cnt0[i - 1] + (nums[i - 1] === 0)
    cnt1[i] = cnt1[i - 1] + (nums[i - 1] === 1)
  }
  let max = 0; const ans = []
  for (let i = 0; i <= n; i++) {
    score[i] = cnt0[i] + cnt1[n] - cnt1[i]
    max = Math.max(max, score[i])
  }
  for (let i = 0; i <= n; i++) {
    if (score[i] === max) ans.push(i)
  }
  return ans
}
