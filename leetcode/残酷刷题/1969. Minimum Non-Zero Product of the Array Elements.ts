function qpow (a: bigint, b: bigint, p: bigint) {
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return ans
}
function minNonZeroProduct (p: number): number {
  const P = BigInt(1e9 + 7); const p_b = BigInt(p)
  const a = 1n << p_b; const b = 1n << (p_b - 1n)
  const m1 = (a - 1n) % P; const m2 = (a - 2n) % P
  return Number(m1 * qpow(m2, b - 1n, P) % P)
};
