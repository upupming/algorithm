/**
 * @param {number[]} nums
 * @param {number[]} numsDivide
 * @return {number}
 */
const minOperations = function (nums, nd) {
  nums.sort((a, b) => a - b)
  const n = nums.length

  const gcd = (a, b) => b ? gcd(b, a % b) : a
  let d = nd[0]
  for (let i = 1; i < nd.length; i++) d = gcd(d, nd[i])

  let mi
  for (let i = 0; i < n; i++) {
    if (d % nums[i] === 0) {
      mi = i
      break
    }
  }
  if (mi == null) return -1
  return mi
}
