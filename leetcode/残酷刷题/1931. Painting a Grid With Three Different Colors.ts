function colorTheGrid (m: number, n: number): number {
  const s = Math.pow(3, m)
  const dp = [...Array<number>(n)].map(() => Array<number>(s).fill(0))
  const possibleStates = []
  for (let i = 0; i < s; i++) {
    let ok = true
    for (let k = 0; k < m - 1; k++) {
      if (Math.ceil(i / Math.pow(3, k)) % 3 === Math.ceil(i / Math.pow(3, k + 1)) % 3) {
        ok = false
        break
      }
    }
    if (ok) {
      dp[0][i] = 1
      possibleStates.push(i)
    }
  }
  for (let i = 1; i < n; i++) {
    for (let j = 0; j < possibleStates.length; j++) {
      for (let k = 0; k < possibleStates.length; k++) {
        let ok = true
        for (let l = 0; l < m; l++) {
          if (Math.ceil(possibleStates[j] / Math.pow(3, l)) % 3 === Math.ceil(possibleStates[k] / Math.pow(3, l)) % 3) {
            ok = false
            break
          }
        }
        if (ok) {
          dp[i][possibleStates[j]] += dp[i - 1][possibleStates[k]]
          dp[i][possibleStates[j]] %= 1e9 + 7
        }
      }
    }
  }
  let ans = 0
  for (let i = 0; i < possibleStates.length; i++) {
    ans += dp[n - 1][possibleStates[i]]
    ans %= 1e9 + 7
  }
  return ans
};
