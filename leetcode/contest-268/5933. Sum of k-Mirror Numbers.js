/**
 * @param {number} k
 * @param {number} n
 * @return {number}
 */
const kMirror = function (k, n) {
  let ans = 0; let cnt = 0
  const isM = (s) => s === s.split('').reverse().join('')

  // 枚举长度
  for (let len = 1; cnt < n; len++) {
    dfs([], len)
  }

  function dfs (cur, len) {
    if (cnt >= n) return
    const h = Math.floor((len + 1) / 2)
    // console.log(cur, cur.length, len, h, cur.length === h)
    if (cur.length === h) {
      const tmp = cur.slice()
      for (let i = h; i < len; i++) {
        tmp[i] = tmp[len - 1 - i]
      }
      const num = Number(tmp.join(''))
      const s = num.toString(k)
      // console.log(num, s)
      if (isM(s)) {
        // console.log(num)
        cnt++
        ans += num
      }
      return
    }
    // console.assert(cur.length !== h)
    for (let i = 0; i <= 9; i++) {
      if (!cur.length && i === 0) continue
      cur.push(i)
      dfs(cur, len)
      cur.pop()
    }
  }

  // for (let i = 1, c = 0;c < n;i++) {
  //     const s = i.toString(k)
  //     const t = i.toString(10)
  //     if (isM(t)) {
  //         c++
  //         ans += i
  //         console.log(i, s, s.split('').reverse().join(''))
  //     }
  // }
  return ans
}
