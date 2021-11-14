let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)

  for (let i = 1, kase = 1; kase <= t; kase++) {
    const [n] = lines[i].split(' ').map(Number)
    let p = lines[i + 1].split('').map(Number)
    // console.log(p)
    const solve = () => {
      let cur = 0
      while (true) {
        let remain = false
        const n = p.length
        const p1 = []

        for (let i = 0; i < n; i++) {
          if (p[i] === cur && i + 1 < n && p[i + 1] === (cur + 1) % 10) {
            p1.push((cur + 2) % 10)
            i = i + 1
          } else {
            p1.push(p[i])
          }
          const k = p1.length - 1; const l = k - 1
          if (l >= 0 && p1[k] === (p1[l] + 1) % 10) remain = true
        }

        if (!remain) {
          // console.log(cur, cnt, cnt[cur])
          return p1.join('')
        }
        cur = (cur + 1) % 10
        p = p1
      }
    }

    i += 2
    console.log(`Case #${kase}: ${solve()}`)
  }
})
