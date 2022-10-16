/**
 * @param {number[]} nums
 * @param {number} minK
 * @param {number} maxK
 * @return {number}
 */
const countSubarrays = function (nums, minK, maxK) {
  const n = nums.length
  const count = (l, r) => {
    // console.log(l, r, nums[l], nums[r])
    let ans = 0
    let minKI = l - 1; let maxKI = l - 1
    for (let i = l; i <= r; i++) {
      if (nums[i] === minK) minKI = i
      if (nums[i] === maxK) maxKI = i

      // console.log(i, minKI, maxKI)
      ans += Math.min(minKI, maxKI) - l + 1
    }
    return ans
  }
  let ans = 0; let l = -1
  for (let i = 0; i < n; i++) {
    if (nums[i] < minK || nums[i] > maxK) {
      // [l+1, i-1]
      ans += count(l + 1, i - 1)
      l = i
    }
  }
  ans += count(l + 1, n - 1)
  return ans
}
