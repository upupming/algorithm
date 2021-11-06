let input = ''
process.stdin.on('data', (data) => input += data)
process.stdin.on('end', () => {
  const arr = input.replace(/\n/g, ' ').split(' ')
  const s2pos = (s) => {
    return [s.charCodeAt(0) - 'a'.charCodeAt(0) + 1, s.charCodeAt(1) - '0'.charCodeAt(0)]
  }
  // 车
  const pos0 = s2pos(arr[0])
  // 马
  const pos1 = s2pos(arr[1])
  // console.log(pos0, pos1)
  const valid = (i, j) => i >= 1 && i <= 8 && j >= 1 && j <= 8
  const getPossible = (pos) => {
    const dx = [2, 2, 1, 1, -2, -2, -1, -1]
    const dy = [1, -1, 2, -2, 1, -1, 2, -2]
    const ans = []
    for (let i = 0; i < dx.length; i++) {
      const x = pos[0] + dx[i]; const y = pos[1] + dy[i]
      if (valid(x, y)) ans.push([x, y])
    }
    return ans
  }
  const equal = (a, b) => a[0] === b[0] && a[1] === b[1]
  const canReach = (pos, next) => {
    const possible = getPossible(pos)
    // if (equal(pos, [3, 4])) {
    //   console.log(possible)
    // }
    for (const p of possible) {
      if (equal(p, next)) return true
    }
    return false
  }
  let ans = 0
  for (let i = 1; i <= 8; i++) {
    for (let j = 1; j <= 8; j++) {
      if (equal([i, j], pos0) || equal([i, j], pos1)) continue
      // 车能吃新马
      if (pos0[0] === i || pos0[1] === j) continue
      // 新马能吃车
      if (canReach([i, j], pos0)) continue
      // 马能吃新马
      if (canReach([i, j], pos1)) continue
      // console.log(i, j)
      ans++
    }
  }
  console.log(ans)
})
