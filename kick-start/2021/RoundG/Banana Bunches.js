let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let i = 1, kase = 1; kase <= t; kase++) {
    const [n, k] = lines[i].split(' ').map(Number)
    const b = lines[i + 1].split(' ').map(Number)

    const solve = () => {
      const sum = [0]
      for (let i = 1; i <= n; i++) sum[i] = sum[i - 1] + b[i - 1]

      let ans = Infinity
      for (let i = 1; i <= n; i++) {
        for (let j = i; j <= n; j++) {
          const s1 = sum[j] - sum[i - 1]
          if (s1 === k) {
            ans = Math.min(ans, j - i + 1)
            continue
          }
          if (s1 > k) break
          const rest = k - s1
          // 这一步可以动态维护 Best[j+1] 来实现 O(1) 时间的复杂度
          // 但是实际上必须从后往前枚举 i, j
          for (let k = j + 1; k <= n; k++) {
            const lSum = rest + sum[k - 1]
            let [l, r] = [k, n]
            while (l < r) {
              const mid = l + r >> 1
              if (sum[mid] >= lSum) r = mid
              else l = mid + 1
            }
            if (sum[l] === lSum) {
              ans = Math.min(ans, j - i + 1 + l - k + 1)
            }
          }
        }
      }

      return ans === Infinity ? -1 : ans
    }

    console.log(`Case #${kase}: ${solve()}`)

    i += 2
  }
})
