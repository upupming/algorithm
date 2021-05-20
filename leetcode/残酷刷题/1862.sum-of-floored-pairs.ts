/*
 * @lc app=leetcode id=1862 lang=typescript
 *
 * [1862] Sum of Floored Pairs
 * 转换成统计每个商（1~1e5）有出现多少次，枚举每个数 x 作为除数，被除数的范围在 [0, x), [x, 2x) ... 之间分别对应商 0, 1, ...，因此我们用 cnt[y] 表示 <= y 的数的个数，一趟预处理统计出 cnt，然后枚举每个 x 来得到答案
 */

// @lc code=start
function sumOfFlooredPairs (nums: number[]): number {
  const [N, n, P] = [1e5 + 10, nums.length, 1e9 + 7]
  const a: number[] = Array(N).fill(0); const cnt: number[] = Array(N).fill(0)
  let numsMax = 0
  for (let i = 0; i < n; i++) {
    a[nums[i]]++
    numsMax = Math.max(numsMax, nums[i])
  }
  for (let i = 1; i <= numsMax; i++) {
    cnt[i] = cnt[i - 1] + a[i]
  }
  let ans = BigInt(0)
  // 两重循环最坏复杂度是 O(numsMax*(1/1 + 1/2...)) 的（nums[i] 各不相同），调和级数，因此是 O(n log n) 的
  for (let i = 1; i <= numsMax; i++) {
    // 枚举所有的商
    for (let j = 0; ; j++) {
      const [minVal, maxVal] = [j * i, (j + 1) * i - 1]
      if (minVal > numsMax) break
      ans = ans + BigInt(cnt[Math.min(maxVal, numsMax)] - cnt[Math.max(minVal, 1) - 1]) * BigInt(j) * BigInt(a[i])
    }
  }
  return Number(ans % BigInt(P))
};
// @lc code=end
