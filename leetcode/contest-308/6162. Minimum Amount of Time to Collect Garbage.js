/**
 * @param {string[]} garbage
 * @param {number[]} travel
 * @return {number}
 */
const garbageCollection = function (g, t) {
  const s = 'PGM'
  const idx = Array(3).fill(0)
  const n = g.length
  for (let k = 0; k < 3; k++) {
    const ch = s[k]
    for (let i = 0; i < n; i++) {
      if (g[i].includes(ch)) idx[k] = i + 1
    }
  }
  let ans = 0; const sum = [0]; const s1 = []
  for (let i = 1; i < n; i++) {
    sum[i] = sum[i - 1] + t[i - 1]
  }
  const cnt = (s, ch) => {
    let ans = 0
    for (const c of s) ans += ch === c
    return ans
  }
  for (let k = 0; k < 3; k++) {
    s1[k] = [0]
    for (let i = 1; i <= n; i++) {
      s1[k][i] = s1[k][i - 1] + cnt(g[i - 1], s[k])
    }
  }
  for (let k = 0; k < 3; k++) {
    if (idx[k] > 0) {
      ans += s1[k][idx[k]] + sum[idx[k] - 1]
    }
  }
  return ans
}
