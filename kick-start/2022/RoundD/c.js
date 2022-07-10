let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 0; kase < t; kase++) {
    const [n] = lines[kase * 4 + 1].split(' ').map(Number)
    const s = lines[kase * 4 + 2].split(' ').map(Number)
    const [m] = lines[kase * 4 + 3].split(' ').map(Number)
    const k = lines[kase * 4 + 4].split(' ').map(Number)

    const pos = Array(3000).fill(0).map(() => [])
    for (let i = 0; i < m; i++) {
      pos[k[i]].push(i)
    }

    const solve = (i) => {
      if (i === n - 1) return pos[s[i]].map((p) => [p, 0])
      const ans = []
      const last = solve(i + 1)
      for (const p of pos[s[i]]) {
        let cost = 1e10
        for (const [lp, lc] of last) {
          cost = Math.min(cost, lc + Math.abs(p - lp))
        }
        ans.push([p, cost])
      }
      ans.sort((a, b) => a[1] - b[1])
      while (ans[ans.length - 1][1] - ans[0][1] >= m) ans.pop()
      return ans
    }

    console.log(`Case #${kase + 1}: ${solve(0).reduce((p, c) => Math.min(p, c[1]), 1e10)}`)
  }
})
