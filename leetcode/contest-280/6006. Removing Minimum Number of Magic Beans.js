/**
 * @param {number[]} beans
 * @return {number}
 */
const minimumRemoval = function (b) {
  b.sort((a, b) => a - b)
  const sum = []; const n = b.length
  sum[-1] = 0
  for (let i = 0; i < n; i++) sum[i] = sum[i - 1] + b[i]
  let ans = 1e11
  for (let i = 0; i < n; i++) {
    const c = sum[i - 1] + (sum[n - 1] - sum[i - 1] - b[i] * (n - i))
    ans = Math.min(ans, c)
  }
  return ans
}
