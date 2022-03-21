let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    // const n = Number(lines[2 * kase - 1])
    const a = lines[2 * kase].split('')
    const n = a.length
    const x = []
    for (let i = 0; i < n; i++) {
      if (a[i] === '?') x.push(i)
    }
    let ok = false
    const check_1 = (b, x, y) => {
      if (y >= n) return true
      for (let i = x, j = y; i < j; i++, j--) {
        if (b[i] !== b[j]) return true
      }
      return false
    }
    function check (b) {
      for (let i = 0; i < n; i++) {
        const j = i + 5 - 1; const k = i + 6 - 1
        if (!check_1(b, i, j)) return false
        if (!check_1(b, i, k)) return false
      }
      return true
    }
    for (let i = 0; i < 1 << x.length; i++) {
      const b = a.slice()
      for (let j = 0; j < x.length; j++) {
        if (i >> j & 1) {
          b[x[j]] = '1'
        } else {
          b[x[j]] = '0'
        }
      }
      if (check(b)) {
        ok = true
        break
      }
    }

    console.log(`Case #${kase}: ${ok ? 'POSSIBLE' : 'IMPOSSIBLE'}`)
  }
})
