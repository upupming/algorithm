// 有一个坑的点是 (1e9+7)^2 在 JS 里面会溢出
const qpow = (a1: number, b1: number, p1: number) => {
  let a = BigInt(a1); let b = BigInt(b1); const p = BigInt(p1)
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return Number(ans)
}

function maxProfit (inventory: number[], orders: number): number {
  const P = 1e9 + 7; const n = inventory.length
  inventory.sort((a, b) => b - a)
  inventory.push(0)
  const div2 = qpow(2, P - 2, P)

  let i = 0
  while (i < n && inventory[i] === inventory[i + 1]) i++
  let ans = 0
  while (orders) {
    // 最多可以拿的轮数
    const max = inventory[i] - inventory[i + 1]
    const n = Math.min(
      // 每轮可以拿 i+1 次，不超过 orders 次
      ~~(orders / (i + 1)),
      max
    )
    // n 轮里面，拿的价值为 (i+1) * (inventory[i], inventory[i]-1,...)
    ans = ans + Number(BigInt(i + 1) * BigInt(
      inventory[i] + (inventory[i] - n + 1)
    ) % BigInt(P) * BigInt(n) % BigInt(P) * BigInt(div2) % BigInt(P))
    ans %= P
    orders -= (i + 1) * n
    // console.log(orders, max, n, i + 1, inventory[i], inventory[i] - n + 1, ans)
    // 拿了 n 轮之后，剩下一轮不完全拿
    if (n < max) {
      const now = inventory[i] - n
      ans = ans + now * orders % P
      ans %= P
      // console.log(now, orders, ans)
      orders = 0
    }
    i++
  }
  return ans
};
