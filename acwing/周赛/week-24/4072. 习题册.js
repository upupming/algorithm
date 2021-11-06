let input = ''
process.stdin.on('data', (data) => input += data)
process.stdin.on('end', () => {
  const arr = input.split('\n').map(line => line.split(' ').map(Number))
  const n = arr[0][0]
  const p = arr[1]
  const a = arr[2]
  const b = arr[3]
  const m = arr[4][0]
  const c = arr[5]
  // console.log(n, p, a, b, m, c)
  const c2Arr = [...Array(4)].map(() => []); const pt = Array(4).fill(0)
  for (let i = 0; i < n; i++) {
    c2Arr[a[i]].push(i)
    c2Arr[b[i]].push(i)
  }
  for (const arr of c2Arr) {
    arr.sort((i, j) => p[i] - p[j])
  }
  const ans = []; const used = new Set()
  for (let i = 0; i < m; i++) {
    const k = c[i]
    // console.log(i, k)
    while (pt[k] < c2Arr[k].length && used.has(c2Arr[k][pt[k]])) pt[k]++
    if (pt[k] >= c2Arr[k].length) {
      ans.push(-1)
      continue
    }
    const cur = c2Arr[k][pt[k]]
    ans.push(p[cur])
    used.add(cur)
    pt[k]++
  }
  // console.log(ans)
  console.log(ans.join(' '))
})
