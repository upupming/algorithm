function numberOfGoodSubsets (nums: number[]): number {
  const primes = []; const st = []; const cnt = []; const P = 1e9 + 7
  for (let i = 2; i <= 30; i++) {
    if (!st[i])primes.push(i)
    for (let j = 0; primes[j] <= 30 / i; j++) {
      st[primes[j] * i] = true
      if (i % primes[j] === 0) break
    }
  }
  nums.forEach(x => { cnt[x] ??= 0, cnt[x]++ })
  const n = primes.length
  const dp = Array(1 << n).fill(0), dp[0] = 1
  for (const v in cnt) {
    if (v === '1') continue
    const t = cnt[v]
    const e = encoding(Number(v))
    if (e === -1) continue
    for (let i = (1 << n) - 1; i >= 1; i--) {
      if ((i - e) === (i ^ e)) {
        dp[i] += dp[i - e] * t
        dp[i] %= P
      }
    }
  }
  let ans = 0
  for (let i = (1 << n) - 1; i >= 1; i--) {
    ans = (ans + dp[i]) % P
  }
  for (let i = 0; i < cnt[1] || 0; i++) {
    ans = (ans * 2) % P
  }
  return ans

  function encoding (x: number) {
    let ans = 0
    for (let i = 0; i < n; i++) {
      const p = primes[i]
      if (x % p === 0) {
        ans += 1 << i
        x /= p
      }
      if (x % p === 0) return -1
    }
    return ans
  }
};
