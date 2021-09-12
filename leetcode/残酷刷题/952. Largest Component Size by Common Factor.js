/**
 * @param {number[]} nums
 * @return {number}
 */
let ok = false
const primes = []; const st = []
const largestComponentSize = function (nums) {
  if (!ok) {
    // 求 [2, max] 里面所有的质数，质数不会很多，素数定理表示，π(n)（不大于n的素数之数量）：n=10^5	为 9,592
    for (let i = 2; i <= 1e3; i++) {
      if (!st[i]) primes.push(i)
      for (let j = 0; primes[j] * i <= 1e3; j++) {
        st[primes[j] * i] = true
        if (i % primes[j] === 0) break
      }
    }
    ok = true
  }

  const fa = [...Array(Math.max(...nums) + 1)].map((_, idx) => idx)
  const get = (x) => {
    if (fa[x] === x) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x, y) => {
    const [fx, fy] = [get(x), get(y)]
    fa[fx] = fy
  }

  for (const num of nums) {
    let x = num
    for (const p of primes) {
      if (p > x) break
      if (x % p === 0) {
        merge(p, num)
        while (x % p === 0) x /= p
      }
    }
    if (x > 1) merge(x, num)
  }
  const sz = fa.map(_ => 0)
  nums.forEach(x => sz[get(x)] += 1)
  return nums.reduce((p, c) => Math.max(p, sz[get(c)]), 0)
}
