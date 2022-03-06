function countSubstrings (s: string, t: string): number {
  const m = s.length; const n = t.length
  s = '#' + s, t = '#' + t
  let ans = 0
  const left = Array(m + 2).fill(0).map(() => Array<number>(n + 2).fill(0))
  const right = Array(m + 2).fill(0).map(() => Array<number>(n + 2).fill(0))
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (s[i] === t[j]) left[i][j] = left[i - 1][j - 1] + 1
      else left[i][j] = 0
    }
  }
  for (let i = m; i >= 1; i--) {
    for (let j = n; j >= 1; j--) {
      if (s[i] === t[j]) right[i][j] = right[i + 1][j + 1] + 1
      else right[i][j] = 0
    }
  }
  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (s[i] !== t[j]) {
        ans += (left[i - 1][j - 1] + 1) * (right[i + 1][j + 1] + 1)
      }
    }
  }
  return ans
};
