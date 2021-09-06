function minNumberOfSemesters (n: number, relations: number[][], k: number): number {
  const dep = Array<number>(n).fill(0)
  for (const r of relations) {
    dep[r[1] - 1] += 1 << (r[0] - 1)
  }
  const prev = Array(1 << n).fill(0)
  for (let i = 0; i < 1 << n; i++) {
    for (let k = 0; k < n; k++) {
      if (i >> k & 1) {
        prev[i] |= dep[k]
      }
    }
  }
  const cntOnes = (i: number) => {
    let ans = 0
    while (i) {
      ans += i & 1
      i >>= 1
    }
    return ans
  }
  const dp = Array<number>(1 << n).fill(1e10)
  dp[0] = 0
  for (let i = 0; i < 1 << n; i++) {
    for (let j = i; j >= 0; j = (j - 1) & i) {
      if (cntOnes(i) - cntOnes(j) <= k && ((prev[i] & j) === prev[i])) {
        dp[i] = Math.min(dp[i], dp[j] + 1)
      }
      if (j === 0) break
    }
  }
  return dp.pop()!
};
