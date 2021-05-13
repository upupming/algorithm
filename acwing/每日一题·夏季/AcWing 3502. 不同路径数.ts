const log = console.log.bind(console)

process.stdin.resume()
process.stdin.setEncoding('utf8')

let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})
process.on('SIGINT', function () {
  main()
})

const dx = [0, 1, 0, -1]
const dy = [1, 0, -1, 0]
function main () {
  const inputArray = input.split('\n'); let inputIndex = 0
  const [n, m, k] = inputArray[inputIndex++].split(' ').map(Number)

  const a: number[][] = []

  for (let i = 0; i < n; i++) {
    a[i] = inputArray[inputIndex++].split(' ').map(Number)
  }

  const ans = new Set<number>()
  const valid = (i: number, j: number) => {
    return i >= 0 && i < n && j >= 0 && j < m
  }
  const dfs = (i: number, j: number, cnt: number, path: number) => {
    if (cnt === k + 1) {
      ans.add(path)
      return
    }
    for (let k = 0; k < 4; k++) {
      const x = i + dx[k]; const y = j + dy[k]
      if (!valid(x, y)) continue
      dfs(x, y, cnt + 1, path * 10 + a[x][y])
    }
  }

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      dfs(i, j, 1, a[i][j])
    }
  }

  log(ans.size)
}
