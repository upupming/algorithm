/**
 * @param {string[]} ideas
 * @return {number}
 */
const distinctNames = function (is) {
  const s = new Set(is)
  // cnt[x][y] 表示把首字母从 x 改成 y 以后就不在 ideas 里的字符串数量
  const cnt = {}
  for (const t of is) {
    const old = t[0]
    cnt[old] ??= {}
    for (let i = 0; i < 26; i++) {
      const now = String.fromCharCode('a'.charCodeAt(0) + i)
      cnt[old][now] ??= 0
      if (!s.has(now + t.slice(1))) cnt[old][now]++
    }
  }
  let ans = 0
  for (const t of is) {
    for (let i = 0; i < 26; i++) {
      const y = String.fromCharCode('a'.charCodeAt(0) + i)
      if (s.has(y + t.slice(1))) continue
      ans += cnt[y]?.[t[0]] ?? 0
    }
  }
  return ans
}

/*
["aaa","baa","caa","bbb","cbb","dbb"]
2
*/
