let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    let [r, a, b] = lines[kase].split(' ').map(Number)
    let ans = 0; let f = 1
    while (r) {
      ans += Math.PI * r * r
      if (f) r = Math.floor(r * a)
      else r = Math.floor(r / b)
      f = !f
    }
    console.log(`Case #${kase}: ${ans}`)
  }
})
