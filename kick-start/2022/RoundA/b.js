let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const x = lines[kase]
    const a = x.split('').map(Number)
    const sum = a.reduce((p, c) => p + c, 0)
    const y = ((9 - sum) % 9 + 9) % 9
    let idx = -1

    for (let i = 0; i < a.length; i++) {
      if (a[i] > y) {
        if (y === 0) {
          if (i !== 0) {
            idx = i
            break
          }
        } else {
          idx = i
          break
        }
      }
    }

    let ans = a.reduce((p, c, i) => {
      if (i === idx) return p + y + c
      else return p + c
    }, '')
    if (idx === -1 || idx >= a.length) ans += y
    console.log(`Case #${kase}: ${ans}`)
  }
})
