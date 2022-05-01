/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} p
 * @return {number}
 */
const countDistinct = function (nums, k, p) {
  const n = nums.length
  const s = new Set(); const P = 13331; const Q = 1e4 + 7; const Q1 = 1e5 + 7; const Q2 = 1e6 + 7
  const f = [0]; const g = [1]; const cnt = [0]
  const f1 = [0]; const g1 = [1]
  const f2 = [0]; const g2 = [1]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P + nums[i - 1]) % Q
    g[i] = (g[i - 1] * P) % Q
    f1[i] = (f1[i - 1] * P + nums[i - 1]) % Q1
    g1[i] = (g1[i - 1] * P) % Q1
    f2[i] = (f2[i - 1] * P + nums[i - 1]) % Q2
    g2[i] = (g2[i - 1] * P) % Q2
    cnt[i] = cnt[i - 1] + (nums[i - 1] % p === 0 ? 1 : 0)
  }
  for (let i = 1; i <= n; i++) {
    for (let j = i; j <= n; j++) {
      const h = ((f[j] - (f[i - 1] * g[j - i + 1])) % Q + Q) % Q
      const h1 = ((f1[j] - (f1[i - 1] * g1[j - i + 1])) % Q1 + Q1) % Q1
      const h2 = ((f2[j] - (f2[i - 1] * g2[j - i + 1])) % Q2 + Q2) % Q2
      const c = cnt[j] - cnt[i - 1]
      if (c <= k) s.add(`${h}_${h1}_${h2}`)
    }
  }
  // console.log(s)
  return s.size
}
