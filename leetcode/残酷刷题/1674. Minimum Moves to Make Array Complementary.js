/**
 * @param {number[]} nums
 * @param {number} limit
 * @return {number}
 */
const minMoves = function (nums, limit) {
  const n = nums.length; const diff = Array(2 * limit + 2).fill(0)
  for (let i = 0, j = n - 1; i < j; i++, j--) {
    const [a, b] = [nums[i], nums[j]].sort((a, b) => a - b)
    // 这一对数对于目标 sum 的修改次数的贡献
    // [2, a+1) 需要 2 次改变
    // [a+1, a+b) 需要 1 次改变
    // [a+b, a+b+1) 需要 0 次改变
    // [a+b+1, b+limit] 需要 1 次改变
    // [b+limit+1, limit+limit] 需要 2 次改变
    diff[2] += 2, diff[a + 1] -= 2
    diff[a + 1] += 1, diff[a + b] -= 1
    diff[a + b + 1] += 1, diff[b + limit + 1] -= 1
    diff[b + limit + 1] += 2, diff[2 * limit + 1] -= 1
  }
  let ans = n
  for (let sum = 2; sum <= 2 * limit; sum++) {
    diff[sum] += diff[sum - 1]
    ans = Math.min(ans, diff[sum])
  }
  return ans
}
