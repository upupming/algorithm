/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const countPairs = function (nums, k) {
  const n = nums.length
  const M = 1e5 + 10
  const sum = Array(M).fill(0)
  for (const x of nums) sum[x]++
  for (let i = 1; i <= k; i++) {
    for (let j = i + i; j < M; j += i) {
      sum[i] += sum[j]
    }
  }
  let ans = 0
  for (const x of nums) {
    const g = gcd(x, k)
    ans += sum[k / g]

    if ((x * x) % k === 0) ans--
  }
  return ans / 2
}

function gcd (x, y) {
  return y ? gcd(y, x % y) : x
}
