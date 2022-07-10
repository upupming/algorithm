let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const [n, m] = lines[kase * 2 - 1].split(' ').map(Number)
    const a = lines[kase * 2].split(' ').map(Number).sort((a, b) => b - a)
    let sum = 0
    a[-1] = 0
    for (let i = -1; i < a.length; i++) {
      sum += a[i]
      if (i === m - 2) {
        // [m-1, n-1]
        // console.log(((n - m + 1) % 2) ? a[(m + n - 2) / 2] : ((a[(m + n - 2 - 1) / 2] + a[(m + n - 2 + 1) / 2]) / 2))
        sum += ((n - m + 1) % 2) ? a[(m + n - 2) / 2] : ((a[(m + n - 2 - 1) / 2] + a[(m + n - 2 + 1) / 2]) / 2)
        break
      }
    }
    console.log(`Case #${kase}: ${sum}`)
  }
})
