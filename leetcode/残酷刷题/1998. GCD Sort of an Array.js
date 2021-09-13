/**
 * @param {number[]} nums
 * @return {boolean}
 */
const P = Math.sqrt(3e5 + 10)
const gcdSort = function (nums) {
  const primes = []; const st = []
  for (let i = 2; i <= P; i++) {
    if (!st[i]) primes.push(i)
    for (let j = 0; primes[j] * i <= P; j++) {
      st[primes[j] * i] = true
      if (i % primes[j] === 0) break
    }
  }

  const fa = [...Array(1e5 + 10)].map((_, idx) => idx)
  const get = (x) => {
    if (fa[x] === x) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x, y) => {
    const fx = get(x); const fy = get(y)
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
    if (x > 1) merge(num, x)
  }

  const sorted = nums.slice().sort((a, b) => a - b)
  for (let i = 0; i < nums.length; i++) {
    if (nums[i] !== sorted[i]) {
      if (get(nums[i]) !== get(sorted[i])) return false
    }
  }
  return true
}
