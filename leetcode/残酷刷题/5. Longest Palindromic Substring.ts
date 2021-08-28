function longestPalindrome (s: string): string {
  const n = s.length
  const dp = [...Array(n)].map(() => Array<boolean>(n))
  let ans = ''
  const assign = (i: number, j: number, val: boolean) => {
    dp[i][j] = val
    if (val && ans.length < j - i + 1) ans = s.slice(i, j + 1)
  }
  for (let i = 0; i < n; i++) {
    assign(i, i, true)
    assign(i, i + 1, s[i] === s[i + 1])
  }
  for (let len = 3; len < n; len++) {
    for (let i = 0; i + len - 1 < n; i++) {
      const j = i + len - 1
      assign(i, j, (s[i] === s[j]) && dp[i + 1][j - 1])
    }
  }
  return ans
};
