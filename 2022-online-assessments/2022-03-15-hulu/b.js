/*
2 6
-****-
-****-
2 2
**
**

3
*/
let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const [m, n] = s[0].split(' ').map(Number)
  const g = s.slice(1, 1 + m).map(x => x.split(''))
  const [a, b] = s[1 + m].split(' ').map(Number)
  const p = s.slice(2 + m, 2 + m + a).map(x => x.split(''))

  const match = (i, j) => {
    for (let x = 0; x < a; x++) {
      const ii = i + x
      if (ii >= m) return false
      for (let y = 0; y < b; y++) {
        const jj = j + y
        if (jj >= n) return false

        if (g[ii][jj] !== p[x][y]) return false
      }
    }
    return true
  }

  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (match(i, j)) ans++
    }
  }
  console.log(ans)
}
