/*
f[i] 表示 1~i 递增
g[i] 表示 i~n 递增
f[i-1] && g[i+1] && nums[i - 1] < nums[i + 1]
*/
function canBeIncreasing (nums: number[]): boolean {
  const n = nums.length
  nums.unshift(-1)
  nums.push(1e5)
  const [f, g] = [Array<boolean>(n + 2).fill(false), Array<boolean>(n + 2).fill(false)]
  f[0] = true
  for (let i = 1; i <= n; i++) {
    if (f[i - 1] && nums[i] > nums[i - 1]) {
      f[i] = true
    }
  }
  g[n + 1] = true
  for (let i = n; i >= 1; i--) {
    if (g[i + 1] && nums[i] < nums[i + 1]) {
      g[i] = true
    }
  }
  for (let i = 1; i <= n; i++) {
    if (f[i - 1] && g[i + 1] && nums[i - 1] < nums[i + 1]) {
      return true
    }
  }
  return false
};
