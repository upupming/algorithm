function numSubarrayBoundedMax (nums: number[], left: number, right: number): number {
  const n = nums.length
  nums.unshift(1e10)
  nums.push(1e10)
  let stk = [0]
  const lft = []
  const rht = []
  for (let i = 1; i <= n; i++) {
    while (nums[stk[stk.length - 1]] <= nums[i]) {
      stk.pop()
    }
    lft[i] = stk[stk.length - 1]
    stk.push(i)
  }
  stk = [n + 1]
  for (let i = n; i >= 1; i--) {
    while (nums[stk[stk.length - 1]] < nums[i]) {
      stk.pop()
    }
    rht[i] = stk[stk.length - 1]
    stk.push(i)
  }
  let ans = 0
  for (let i = 1; i <= n; i++) {
    if (nums[i] >= left && nums[i] <= right) {
      const len = (i - lft[i]) * (rht[i] - i)
      ans += len
    }
  }
  return ans
};
