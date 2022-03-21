let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const x = lines[kase * 2 - 1]
    const y = lines[kase * 2]
    const n = x.length
    const m = y.length
    let i = 0
    for (let j = 0; i < n && j < m; j++) {
      if (x[i] === y[j]) i++
    }
    console.log(`Case #${kase}: ${i === n ? (m - n) : 'IMPOSSIBLE'}`)
  }
})
