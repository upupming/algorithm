/**
 * @param {number[]} nums
 * @return {number}
 148=1*50+2*49
 x = mi+n(i-1) = (m+n)i-n
 x%i = (-n)%i, 148%50=48=-n+ki
 x%(i-1) = m%(i-1)
 x/i = m+n(i-1)/i
 x/i-1 = mi/(i-1)+n
 */
const minGroupsForValidAssignment = function (nums) {
  const cnt = {}; const n = nums.length
  for (let i = 0; i < n; i++) {
    cnt[nums[i]] ??= 0
    cnt[nums[i]]++
  }
  const a = Object.values(cnt).sort((a, b) => a - b)
  const t = a[0]
  for (let i = t + 1; i >= 2; i--) {
    let ok = true; let g = 0
    for (const x of a) {
      const n = ((i - x) % i + i) % i
      if ((x - n * (i - 1)) % i !== 0 || (x - n * (i - 1)) / i < 0) {
        ok = false
        break
      } else {
        const m = (x - n * (i - 1)) / i
        g += m + n
      }
    }
    if (ok) return g
  }
  return n
}
