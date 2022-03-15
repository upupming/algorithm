let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const a = s[1].split(' ').map(Number)
  const get = (x) => {
    if (x >= a.length) return null
    if (a[x] === -1) return null
    return a[x]
  }
  let ans = 0
  function dfs (x) {
    if (!get(x)) return
    const left = 2 * x + 1
    const right = 2 * x + 2
    if (get(left) === null && get(right) === null) {
      ans++
      return
    }
    if (get(left)) dfs(left)
    if (get(right)) dfs(right)
  }
  dfs(0)
  console.log(ans)
}
