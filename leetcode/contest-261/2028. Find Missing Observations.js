/**
 * @param {number[]} rolls
 * @param {number} mean
 * @param {number} n
 * @return {number[]}
 */
const missingRolls = function (rolls, mean, n) {
  const sum = mean * (rolls.length + n) - rolls.reduce((p, c) => p + c, 0)
  if (sum < n || sum > 6 * n) return []
  const ans = []
  const x = Math.floor(sum / n); const y = sum % n
  for (let i = 0; i < n; i++) {
    if (i < y) ans.push(x + 1)
    else ans.push(x)
  }
  return ans
}
