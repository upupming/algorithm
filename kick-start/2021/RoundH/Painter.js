let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  const mp = {
    R: 0b100,
    Y: 0b010,
    B: 0b001
  }
  mp.O = mp.R + mp.Y
  mp.P = mp.R + mp.B
  mp.G = mp.Y + mp.B
  mp.A = mp.R + mp.Y + mp.B
  for (let i = 1, kase = 1; kase <= t; kase++) {
    const [n] = lines[i].split(' ').map(Number)
    const p = lines[i + 1].split('').map(c => mp[c])
    // console.log(p)

    const solve = () => {
      let ans = 0
      while (true) {
        let remain = false

        for (let i = 0; i < n; i++) {
          if (p[i] > 0) {
            for (let j = 0; j < 3; j++) {
              if (p[i] >> j & 1) {
                ans++; remain = true
                let k = i; let firstGreaterThanZero = -1
                for (; k < n; k++) {
                  if (p[k] >> j & 1) {
                    p[k] -= 1 << j
                    if (p[k] > 0 && firstGreaterThanZero === -1) firstGreaterThanZero = k
                  } else {
                    break
                  }
                }
                // console.log(i, k, 1 << j, p)
                if (firstGreaterThanZero === -1) {
                  i = k - 1
                } else {
                  i = firstGreaterThanZero - 1
                }
                break
              }
            }
          }
        }

        if (!remain) break
      }
      return ans
    }

    i += 2
    console.log(`Case #${kase}: ${solve()}`)
  }
})
