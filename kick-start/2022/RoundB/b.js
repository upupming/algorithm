let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let kase = 1; kase <= t; kase++) {
    const a = BigInt(lines[kase])
    let ans = 0
    for (let x = Number(1); x <= Number(1e5 - 1); x++) {
      if (x <= 9) if (a % BigInt(x) === BigInt(0)) ans++
      let y = BigInt(String(x) + String(x).split('').reverse().join(''))
      if (a % y === BigInt(0)) ans++
      for (let i = 0; i <= 9; i++) {
        y = BigInt(String(x) + i + String(x).split('').reverse().join(''))
        if (a % y === BigInt(0)) ans++
      }
    }
    console.log(`Case #${kase}: ${ans}`)
  }
})
