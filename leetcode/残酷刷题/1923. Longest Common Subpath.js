
const base = BigInt(1e5 + 7); const mod = BigInt(1e9 + 7) * BigInt(1e9 + 9)
const pow = [1n]
for (let i = 1; i <= 1e5; i++) {
  pow[i] = pow[i - 1] * base % mod
}
/**
 * @param {number} n
 * @param {number[][]} paths
 * @return {number}
 */
const longestCommonSubpath = function (n, paths) {
  const cntHash = new Map()
  const s = new Set()

  let l = 0; let r = 1e5
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }

  function valid (len) {
    cntHash.clear()
    for (const p of paths) {
      s.clear()
      let hash = 0n
      for (let i = 0; i < p.length; i++) {
        if (i >= len) { hash -= BigInt(p[i - len]) * pow[len - 1] }
        hash = ((hash % mod + mod) % mod * base + BigInt(p[i])) % mod
        if (i >= len - 1 && !s.has(hash)) {
          s.add(hash)
          if (!cntHash.get(hash)) cntHash.set(hash, 0)
          cntHash.set(hash, cntHash.get(hash) + 1)
        }
      }
    }
    for (const t of cntHash.values()) {
      if (t >= paths.length) return true
    }
    return false
  }

  return l
}
