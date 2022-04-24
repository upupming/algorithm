let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const a = eval(s[0])
  const n = Number(s[1])
  function flat (b, n) {
    if (n === 0) return b
    const c = []
    for (const x of b) {
      if (Array.isArray(x)) c.push(...x)
      else c.push(x)
    }
    return flat(c, n - 1)
  }
  console.log(JSON.stringify(flat(a, n)))
  function print (a) {
    const ans = []
    for (const x of a) {
      if (Array.isArray(x)) ans.push(print(x))
      else ans.push(x)
    }
    return '[' + ans.join(',') + ']'
  }
}

/*
[1,[2,[3,[4]],5]]
2

[1,2,3,[4],5]
*/
