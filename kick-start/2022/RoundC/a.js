let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    let s = lines[kase * 2]
    let hasUpper = false; let hasLower = false; let hasDigit = false; let hasSpe = false
    for (const ch of s) {
      if (ch.charCodeAt(0) >= 'A'.charCodeAt(0) && ch.charCodeAt(0) <= 'Z'.charCodeAt(0)) hasUpper = true
      if (ch.charCodeAt(0) >= 'a'.charCodeAt(0) && ch.charCodeAt(0) <= 'z'.charCodeAt(0)) hasLower = true
      if (ch.charCodeAt(0) >= '0'.charCodeAt(0) && ch.charCodeAt(0) <= '9'.charCodeAt(0)) hasDigit = true
      if ('#@*&'.includes(ch)) hasSpe = true
    }
    if (!hasUpper) s += 'A'
    if (!hasLower) s += 'a'
    if (!hasDigit) s += '1'
    if (!hasSpe) s += '#'
    while (s.length < 7) s += 'A'

    console.log(`Case #${kase}: ${s}`)
  }
})
