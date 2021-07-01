// function pow (a: number, b: number, p: number) {
//   let ans = 1 % p
//   while (b) {
//     if (b & 1) ans = Number(BigInt(ans) * BigInt(a) % BigInt(p))
//     a = Number(BigInt(a) * BigInt(a) % BigInt(p))
//     b >>= 1
//   }
//   return ans
// }
function pow (a: bigint, b: bigint, p: bigint) {
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return ans
}
function waysToBuildRooms (prevRoom: number[]): number {
  const n = prevRoom.length
  const e: number[][] = [...new Array(n)].map(() => [])
  const size: number[] = new Array(n).fill(0)
  const f: Array<bigint> = new Array(n).fill(0n)
  const g: Array<bigint> = new Array(n).fill(0n)
  const p = BigInt(1e9 + 7)

  f[0] = g[0] = 1n
  for (let i = 1; i < n; i++) {
    f[i] = f[i - 1] * BigInt(i) % p
    g[i] = g[i - 1] * pow(BigInt(i), p - 2n, p) % p
  }

  for (let i = 1; i < n; i++) {
    e[prevRoom[i]].push(i)
  }
  return Number(dfs(0))

  function dfs (x: number) {
    let ans = 1n
    for (const y of e[x]) {
      const cnt = dfs(y)
      size[x] += size[y]
      ans = (ans * cnt % p) * g[size[y]] % p
    }
    ans = ans * f[size[x]] % p
    size[x] += 1
    return ans % p
  }
};
