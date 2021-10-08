/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const waysToPartition = function (nums, k) {
  const p = [0]; const s = []; const n = nums.length
  const total = nums.reduce((p, c) => p + c, 0)
  for (let i = 1; i <= n; i++) {
    p[i] = p[i - 1] + nums[i - 1]
  }
  s[n + 1] = 0
  for (let i = n; i >= 1; i--) {
    s[i] = s[i + 1] + nums[i - 1]
  }
  const ch = []; let cnt = {}
  for (let i = 1; i <= n; i++) {
    const newTotal = total - nums[i - 1] + k
    ch[i] = (newTotal % 2 === 0) ? (cnt[newTotal / 2] ?? 0) : 0
    cnt[p[i]] ??= 0, cnt[p[i]] += 1
  }
  cnt = {}
  for (let i = n; i >= 1; i--) {
    const newTotal = total - nums[i - 1] + k
    ch[i] += (newTotal % 2 === 0) ? (cnt[newTotal / 2] ?? 0) : 0
    cnt[s[i]] ??= 0, cnt[s[i]] += 1
  }
  const ans = ch.reduce((p, c) => Math.max(p, c), 0)
  let a = 0
  for (let t = 1; t < n; t++) {
    if (total - p[t] === p[t]) a++
  }
  return Math.max(a, ans)
}
