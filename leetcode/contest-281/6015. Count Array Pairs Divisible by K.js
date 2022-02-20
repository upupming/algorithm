/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */

const gcd = (a, b) => {
  return b ? gcd(b, a % b) : a
}
const getP = (x) => {
  const s = new Set(); const t = new Set()
  for (let i = 1; i * i <= x; i++) {
    if (x % i === 0) {
      s.add(i)
      s.add(x / i)
    }
  }
  for (const x of s) {
    let ok = true
    for (const y of s) {
      if (x < y && y % x === 0) ok = false
    }
    if (ok) t.add(x)
  }
  return t
}
const coutPairs = function (nums, k) {
  const n = nums.length
  const s = new Set()

  for (let i = 1; i * i <= k; i++) {
    if (k % i === 0) {
      s.add(i)
      s.add(k / i)
    }
  }

  const cnt = {}; let ans = 0
  for (let i = 0; i < n; i++) {
    const x = gcd(nums[i], k)
    const y = k / x
    for (const v of s) {
      if (v % y === 0) ans += cnt[v] ?? 0
    }
    // 根据 nums[i] 修改 cnt
    for (const p of getP(nums[i])) {
      const q = gcd(p, k)
      cnt[q] ??= 0
      cnt[q]++
    }
  }
  return ans
}
