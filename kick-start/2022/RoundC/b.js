let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const [n, x, y] = lines[kase].split(' ').map(Number)

    const sum = (1 + n) * n / 2
    if (sum % (x + y) === 0) {
      // 是否分给 a
      const sa = Array(n + 1).fill(0)
      const a = sum / (x + y) * x; const b = sum - a
      const r = a % (1 + n); let times = Math.floor(a / (1 + n))
      const rb = b % (1 + n); const timesB = Math.floor(b / (1 + n))
      if (timesB === 0) {
        for (let i = 1; i <= n; i++) {
          if (i === rb) sa[i] = 0
          else sa[i] = 1
        }
      } else {
        sa[r] = 1
        for (let i = 1; times > 0; i++) {
          if (r === i || r === (n + 1 - i)) continue
          sa[i] = sa[n + 1 - i] = 1
          times -= 1
        }
      }
      console.log(`Case #${kase}: POSSIBLE`)
      let s = ''; let cnt = 0
      for (let i = 1; i <= n; i++) {
        if (sa[i]) {
          if (s.length) s += ' '
          s += i
          cnt++
        }
      }
      console.log(cnt)
      console.log(s)
    } else {
      console.log(`Case #${kase}: IMPOSSIBLE`)
    }
  }
})
