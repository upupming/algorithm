let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let i = 1, kase = 1; kase <= t; kase++) {
    const s = lines[i]
    const f = lines[i + 1]
    const st = new Set(f.split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0)))

    const solve = () => {
      let ans = 0
      for (let i = 0; i < s.length; i++) {
        let cur = Infinity; const t = s[i].charCodeAt(0) - 'a'.charCodeAt(0)
        for (let j = 0; j < 26; j++) {
          if (st.has(j)) {
            const diff = Math.abs(j - t)
            cur = Math.min(cur, diff, 26 - diff)
          }
        }
        ans += cur
      }
      return ans
    }

    i += 2
    console.log(`Case #${kase}: ${solve()}`)
  }
})
