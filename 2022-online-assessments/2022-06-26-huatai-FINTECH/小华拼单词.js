let input = ''

process.stdin.on('data', data => input += data)

process.stdin.on('end', () => {
  const cnt = input.split('\n')[0].split(' ').map(Number)
  let ans = 1e10
  const s = 'huatai'
  for (let ch of s) {
    let c = 0
    for (let i = 0; i < s.length; i++) if (s[i] === ch) c++
    let x = cnt[ch.charCodeAt(0) - 'a'.charCodeAt(0)]
    ans = Math.min(ans, Math.floor(x / c))
  }
  console.log(ans)
})
