let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  let loc = 0
  const [t] = lines[loc++].split(' ').map(Number)
  for (let kase = 0; kase < t; kase++) {
    const [n, m, k] = lines[loc++].split(' ').map(Number)
    const e = Array(n + 1).fill(0).map(() => [])
    const er = Array(n + 1).fill(0).map(() => [])
    for (let i = loc; i < loc + m; i++) {
      // console.log(i, lines[i])
      let [a, b] = lines[i].split(' ').map(Number)
      a--, b--
      // console.log(a, b)
      e[a].push(b)
      er[b].push(a)
    }
    loc += m

    const f = Array(n).fill(1)
    for (let i = 0; i < n; i++) {
      // 第 i 个人是 not innocent 的
      let ok = true

      if (er[i].length > 0) ok = false

      if (ok) {
        f[i] = 0
      }
    }

    // console.log(f)
    console.log(`Case #${kase + 1}: ${f.reduce((p, c) => p + c, 0)}`)
  }
})
