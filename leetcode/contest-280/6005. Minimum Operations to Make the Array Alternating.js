/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumOperations = function (nums) {
  const n = nums.length
  if (n === 1) return 0
  const a = []; const b = []
  for (let i = 0; i < n; i++) {
    if (i % 2 === 0) a.push(nums[i])
    else b.push(nums[i])
  }
  const min = (x) => {
    const m = x.length
    const cnt = {}
    for (const a of x) cnt[a] ??= 0, cnt[a]++
    const cost = []
    for (const key of Object.keys(cnt)) {
      // tuple [cost to change all to this value, value]
      cost.push([m - cnt[key], Number(key)])
    }
    return cost.sort((a, b) => a[0] - b[0])
  }

  const x = min(a); const y = min(b)
  x.push([a.length, 1e5 + 1])
  y.push([b.length, 1e5 + 2])
  if (x[0][1] !== y[0][1]) return x[0][0] + y[0][0]
  else return Math.min(x[0][0] + y[1][0], x[1][0] + y[0][0])
}
