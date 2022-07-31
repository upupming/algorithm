/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number} k1
 * @param {number} k2
 * @return {number}
 */
const minSumSquareDiff = function (nums1, nums2, k1, k2) {
  const k = k1 + k2
  let l = 0; let r = 1e5; const n = nums1.length
  const d = nums1.map((x, i) => Math.abs(x - nums2[i]))
  function valid (x) {
    let cnt = 0
    for (const y of d) {
      cnt += y - Math.min(y, x)
    }
    return cnt <= k
  }
  while (l < r) {
    const mid = l + r >> 1
    if (valid(mid)) r = mid
    else l = mid + 1
  }
  let ans = 0
  const dm = d.map(x => Math.min(x, l)).sort((a, b) => b - a)
  let rest = k - dm.reduce((p, c, i) => p + d[i] - c, 0)
  for (let mm of dm) {
    if (rest && mm > 0) {
      mm--, rest--
    }
    ans += mm * mm
  }
  return ans
}
