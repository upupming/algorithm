let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  let loc = 0
  const [t] = lines[loc++].split(' ').map(Number)
  for (let kase = 0; kase < t; kase++) {
    const [n, m, k] = lines[loc++].split(' ').map(Number)
    const e = Array(n + 1).fill(0).map(() => [])
    for (let i = loc; i < loc + m; i++) {
      let [a, b] = lines[i].split(' ').map(Number)
      a--, b--
      // console.log(a, b)
      e[a].push(b)
    }
    loc += m

    const f = Array(n).fill(1)
    for (let i = 0; i < 1 << n; i++) {
      let ok = true

      let cnt = 0
      for (let j = 0; j < n; j++) {
        if (!((i >> k) & 1)) cnt++
      }
      if (cnt > k) continue

      for (let j = 0; j < n; j++) {
        // j is innocent
        if ((i >> j) & 1) {
          for (const k of e[j]) {
            // k is not innocent
            if (!((i >> k) & 1)) {
              ok = false
              break
            }
          }
        }
        if (!ok) break
      }

      if (ok) {
        for (let j = 0; j < n; j++) {
          // not innocent
          if (!((i >> j) & 1)) {
            f[j] = 0
          }
        }
      }
    }

    // console.log(f)
    console.log(`Case #${kase + 1}: ${f.reduce((p, c) => p + c, 0)}`)
  }
})
