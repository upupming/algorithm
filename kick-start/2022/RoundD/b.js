let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 0; kase < t; kase++) {
    const [n] = lines[kase * 5 + 1].split(' ').map(Number)
    const a = lines[kase * 5 + 2].split(' ').map(Number)
    const [m] = lines[kase * 5 + 3].split(' ').map(Number)
    const b = lines[kase * 5 + 4].split(' ').map(Number)
    const [k] = lines[kase * 5 + 5].split(' ').map(Number)
    // console.log(`Case #${kase + 1}`, n, a, m, b, k)
    // f[i]: 从 a 里面选 i 个数的最大
    const f = Array(n + 1).fill(0)
    let sum = Array(n + 1).fill(0)
    for (let i = 0; i < n; i++) sum[i + 1] = sum[i] + a[i]
    for (let i = 0; i <= n; i++) {
      // 从左侧选 j 个数
      for (let j = 0; j <= i; j++) {
        const k = i - j
        // [0, j-1], [n-k, n-1]
        f[i] = Math.max(f[i], sum[j] + sum[n] - sum[n - k])
      }
    }

    const g = Array(m + 1).fill(0)
    sum = Array(m + 1).fill(0)
    for (let i = 0; i < m; i++) sum[i + 1] = sum[i] + b[i]
    for (let i = 0; i <= m; i++) {
      // 从左侧选 j 个数
      for (let j = 0; j <= i; j++) {
        const k = i - j
        // [0, j-1], [n-k, n-1]
        g[i] = Math.max(g[i], sum[j] + sum[m] - sum[m - k])
      }
    }

    let ans = 0
    for (let i = 0; i <= Math.min(k, n); i++) {
      if (k - i < 0 || k - i > m) continue
      ans = Math.max(ans, f[i] + g[k - i])
    }

    console.log(`Case #${kase + 1}: ${ans}`)
  }
})
