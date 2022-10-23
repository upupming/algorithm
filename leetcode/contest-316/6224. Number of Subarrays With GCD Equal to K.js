/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const subarrayGCD = function (nums, k) {
  const n = nums.length
  let ans = 0
  const gcd = (a, b) => b ? gcd(b, a % b) : a
  for (let i = 0; i < n; i++) {
    let g = nums[i]
    for (let j = i; j < n; j++) {
      g = gcd(g, nums[j])
      if (g === k) ans++
    }
  }
  return ans
}
