/*
对于每一个数，计算最左边、最右边可以到达的地方即可
left[i] 表示左边第一个小于 nums[i] 的下标
right[i] 表示右边第一个小于 nums[i] 的下标
利用单调栈求解
*/

const max = <T>(a: T, b: T) => (a > b ? a : b)
// const log = console.log.bind(console)
// const log = _ => {}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function maxSumMinProduct (nums: number[]): number {
  const n = nums.length
  // 添加哨兵
  nums.unshift(-1)
  nums.push(-1)

  const left: number[] = Array(n + 1); const right: number[] = Array(n + 1); const sum: Array<bigint> = Array(n + 1).fill(BigInt(0))

  let s = [0]
  for (let i = 1; i <= n; i++) {
    while (nums[s[s.length - 1]] >= nums[i]) s.pop()
    left[i] = s[s.length - 1]
    s.push(i)

    sum[i] = sum[i - 1] + BigInt(nums[i])
  }
  s = [n + 1]
  for (let i = n; i >= 1; i--) {
    while (nums[s[s.length - 1]] >= nums[i]) s.pop()
    right[i] = s[s.length - 1]
    s.push(i)
  }

  let ans = 0n; const P = BigInt(1e9 + 7)
  for (let i = 1; i <= n; i++) {
    const l = left[i] + 1; const r = right[i] - 1
    ans = max(ans, (sum[r] - sum[l - 1]) * BigInt(nums[i]))
  }
  return Number(ans % P)
}
