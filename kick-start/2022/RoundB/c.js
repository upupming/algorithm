let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const [_, d] = lines[kase * 2 - 1].split(' ').map(Number)
    const v = lines[kase * 2].split(' ').map(Number)
    const n = v.length
    /*
    dp[i][j][k] = 将区间 i, j 全部变成 k 的开销
    Math.min(dp[i1][j][num(i, i1)], dp[i][j1][num(j1, j)])
    */
    const cache = {}
    const solve = (i, j, k) => {
      console.assert(i >= 0 && i < n)
      console.assert(j >= 0 && j < n)
      if (cache[`${i}_${j}_${k}`] != null) {
        return cache[`${i}_${j}_${k}`]
      }
      while (v[i] === k) i++
      while (v[j] === k) j--
      if (i > j) return 0
      const k1 = v[i]; const k2 = v[j]
      const d1 = Math.abs(k1 - k); const d2 = Math.abs(k2 - k)
      const ans = Math.min(solve(i, j, k1) + Math.min(d1, d - d1), solve(i, j, k2) + Math.min(d2, d - d2))
      if (ans < 0) console.log(i, j, k, k1, k2, d, d1, d2)
      return cache[`${i}_${j}_${k}`] = ans
    }
    console.log(`Case #${kase}: ${solve(0, n - 1, 0)}`)
  }
})
