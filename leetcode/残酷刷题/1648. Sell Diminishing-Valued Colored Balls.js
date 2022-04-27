/**
 * @param {number[]} inventory
 * @param {number} orders
 * @return {number}
 */
const maxProfit = function (inventory, orders) {
  // >= mid 以上的都被售出
  let l = 1; let r = 1e9
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }
  function valid (m) {
    let o = 0
    for (const p of inventory) {
      if (p >= m) o += (p - m + 1)
    }
    return o >= orders
  }
  let sum = 0n; let rest = orders
  // l+1 先全部都选了再说
  for (const p of inventory) {
    if (p >= l + 1) {
      const c = p - (l + 1) + 1
      sum += BigInt(p + l + 1) * BigInt(c) / 2n
      sum %= BigInt(1e9 + 7)
      rest -= c
    }
  }
  // 不够的全部都选 l
  sum += BigInt(rest) * BigInt(l)
  sum %= BigInt(1e9 + 7)
  return sum
}
