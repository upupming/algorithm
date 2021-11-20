let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const s = input.split('\n')[0]
  const n = s.length
  const t = ('#' + s).split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0))
  let [l, r] = [1, n]
  const cnt = [...Array(26)].map(() => Array(n + 1).fill(0))
  for (let i = 0; i < 26; i++) {
    for (let j = 1; j <= n; j++) {
      cnt[i][j] = cnt[i][j - 1] + (t[j] === i)
    }
  }

  const valid = (len) => {
    // 所有长为 len 的都至少存在一个字符 i
    for (let i = 0; i < 26; i++) {
      let ok = true
      for (let j = 1; j + len - 1 <= n; j++) {
        const k = j + len - 1
        const x = cnt[i][k] - cnt[i][j - 1]
        if (x <= 0) {
          ok = false
          break
        }
      }
      if (ok) return true
    }
    return false
  }
  while (l < r) {
    const mid = l + r >> 1
    if (valid(mid)) r = mid
    else l = mid + 1
  }
  console.log(l)
})
