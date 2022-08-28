/**
 * @param {number[]} nums
 * @param {number[]} queries
 * @return {number[]}
 */
const answerQueries = function (nums, queries) {
  const n = nums.length; const m = queries.length
  const sum = [0]
  nums.sort((a, b) => a - b)
  for (let i = 1; i <= n; i++) sum[i] = sum[i - 1] + nums[i - 1]
  return queries.map(q => {
    for (let i = 0; i <= n; i++) {
      if (sum[i] > q) return i - 1
    }
    return n
  })
}
