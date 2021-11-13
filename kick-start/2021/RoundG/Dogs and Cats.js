let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let i = 1, kase = 1; kase <= t; i += 2, kase++) {
    let [n, d, c, m] = lines[i].split(' ').map(Number)
    const s = lines[i + 1]

    const solve = () => {
      let lastDog = -1
      for (let i = 0; i < s.length; i++) {
        if (s[i] === 'D') { lastDog = i }
      }
      for (let i = 0; i <= lastDog; i++) {
        if (s[i] === 'C') {
          c--
          if (c < 0) return 'NO'
        } else if (s[i] === 'D') {
          d--
          if (d < 0) return 'NO'
          c += m
        }
      }

      return 'YES'
    }

    console.log(`Case #${kase}: ${solve()}`)
  }
})
