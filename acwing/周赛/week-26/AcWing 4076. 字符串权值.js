let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  let ans = 1
  const num = input.split('\n')[0].slice(1)
  for (let i = 0; i < num.length; i++) {
    const x = num[i].charCodeAt(0) - '0'.charCodeAt(0)
    if (x === 1) ans += 10
    else ans += x
  }
  console.log(ans)
})
