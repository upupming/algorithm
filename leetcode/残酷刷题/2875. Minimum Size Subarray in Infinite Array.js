/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
const minSizeSubarray = function (nums, t) {
  const n = nums.length; const s = [0]; const mp = {}; let ans = 1e10
  nums = [...nums, ...nums]
  for (let i = 1; i <= 2 * n; i++) {
    s[i] = s[i - 1] + nums[i - 1]
  }
  mp[0] = 0
  for (let i = 1; i <= 2 * n; i++) {
    const r = ((s[i] - t) % s[n] + s[n]) % s[n]
    if (mp[r] != null) {
      const j = mp[r]
      // s[n]*k + [j, i) (即: s[i]-s[j]) = t
      const k = Math.floor((t - (s[i] - s[j])) / s[n])
      // [j, n), [0, i]
      ans = Math.min(ans, k * n + i - j)
    }

    mp[s[i] % s[n]] = i
  }
  return ans === 1e10 ? -1 : ans
}
