/*
 * @lc app=leetcode id=1589 lang=typescript
 *
 * [1589] Maximum Sum Obtained of Any Permutation
 * 看看每个下标出现了多少次，然后将下标按照出现次数排序，将大的数尽量安排到出现次数多的位置
 */

// @lc code=start
function maxSumRangeQuery (nums: number[], requests: number[][]): number {
  const n = nums.length
  const [cnt, diff] = [Array<number>(n + 1).fill(0), Array<number>(n + 1).fill(0)]
  for (const req of requests) {
    diff[req[0]]++
    diff[req[1] + 1]--
  }
  // cnt 的下标从 1 开始，diff 的下标从 0 开始
  for (let i = 1; i <= n; i++) {
    cnt[i] = cnt[i - 1] + diff[i - 1]
  }
  nums.sort((a, b) => -(a - b))
  cnt.shift()
  cnt.sort((a, b) => -(a - b))
  let ans = 0
  for (let i = 0; i < n; i++) {
    // console.log(i, nums[i], cnt[i])
    ans += nums[i] * cnt[i]
  }
  return ans % (1e9 + 7)
};
// @lc code=end
