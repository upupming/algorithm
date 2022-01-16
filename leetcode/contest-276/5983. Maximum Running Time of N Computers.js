/**
 * @param {number} n
 * @param {number[]} batteries
 * @return {number}
 */
const min = (a, b) => a <= b ? a : b
const maxRunTime = function (n, b) {
  const m = b.length
  const ans = 0
  let l = 0n; let r = b.reduce((p, c) => p + BigInt(c), 0n) / BigInt(n)
  while (l < r) {
    const mid = l + r + 1n >> 1n
    if (valid(mid)) l = mid
    else r = mid - 1n
  }
  function valid (mid) {
    const sum = b.reduce((p, c) => p + min(BigInt(c), mid), 0n)
    return sum >= BigInt(n) * mid
  }
  return l
}
