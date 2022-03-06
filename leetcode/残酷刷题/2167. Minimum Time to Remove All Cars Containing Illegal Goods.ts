function minimumTime (s: string): number {
  const n = s.length
  const left = []; const right = []
  left[-1] = 0, right[n] = 0
  for (let i = 0; i < n; i++) {
    if (s[i] === '0') left[i] = left[i - 1]
    else left[i] = Math.min(i + 1, 2 + left[i - 1])
  }
  for (let i = n - 1; i >= 0; i--) {
    if (s[i] === '0') right[i] = right[i + 1]
    else right[i] = Math.min(n - i, 2 + right[i + 1])
  }
  let ans = 1e10
  for (let i = 0; i <= n; i++) {
    ans = Math.min(ans, left[i - 1] + right[i])
    // console.log(i, left[i - 1], right[i], ans)
  }
  return ans
};
