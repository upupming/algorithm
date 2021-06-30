/*
f[i]: max alternating sum end with a[i], with add
g[i]: max alternating sum end with a[i], with minus
add: 动态维护当前 f[i] 的最大值
minus: 动态维护当前 g[i] 的最大值
实际做的时候无需保存 f[i], g[i] 数组
*/
function maxAlternatingSum (nums: number[]): number {
  let [add, minus] = [-1, 0]
  for (let i = 0; i < nums.length; i++) {
    add = Math.max(add, minus + nums[i])
    if (add !== -1) {
      minus = Math.max(minus, add - nums[i])
    }
  }
  return Math.max(add, minus)
};
