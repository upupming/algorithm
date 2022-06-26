let input = ''

process.stdin.on('data', data => input += data)

process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [n] = lines[0].split(' ').map(Number)
  const edges = lines.slice(1, n).map(line => line.split(' ').map(Number))
  const e = Array(n + 1).fill(0).map(() => [])
  for (const [x, y] of edges) {
    e[x].push(y)
    e[y].push(x)
  }
  const fa = Array(n + 1).fill(0).map((_, idx) => idx)
  const sz = Array(n + 1).fill(1)
  const get = (i) => {
    if (fa[i] === i) return i
    return fa[i] = get(fa[i])
  }
  const merge = (i, j) => {
    const fi = get(i); const fj = get(j)
    if (fi === fj) return
    const si = sz[fi]; const sj = sz[fj]
    if (si < sj) {
      fa[fi] = fj
      sz[fj] += si
    } else {
      fa[fj] = fi
      sz[fi] += sj
    }
  }
  let ans = 0; const P = (1e9 + 7)
  const Pn = BigInt(P)
  for (let i = 1; i <= n; i++) {
    let prod = 1n
    for (const j of e[i]) {
      if (j < i) {
        const fi = get(i); const fj = get(j)
        const sj = sz[fj]
        if (fi !== fj) {
          merge(i, j)
          ans += Number(BigInt(sj) * BigInt(i) * prod % Pn)
          ans %= P
        }
        prod += BigInt(sj)
      }
    }
  }
  console.log(ans)
})
