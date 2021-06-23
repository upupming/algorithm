function nthSuperUglyNumber (n: number, primes: number[]): number {
  const m = primes.length
  const p = Array(m).fill(0)
  const arr = [1]
  while (arr.length !== n) {
    let tmp = 1e30
    for (let i = 0; i < m; i++) {
      tmp = Math.min(tmp, arr[p[i]] * primes[i])
    }
    for (let i = 0; i < m; i++) {
      if (tmp === arr[p[i]] * primes[i]) p[i]++
    }
    arr.push(tmp)
  }
  return arr[arr.length - 1]
};
