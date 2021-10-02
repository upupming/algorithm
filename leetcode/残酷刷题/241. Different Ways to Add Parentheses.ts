function diffWaysToCompute (expression: string): number[] {
  const n = expression.length
  const nums: number[] = []
  const ops: string[] = []
  let val = 0
  expression.split('').forEach((ch, i) => {
    if (ch >= '0' && ch <= '9') {
      val = val * 10 + (ch.charCodeAt(0) - '0'.charCodeAt(0))
      if (i + 1 < n && expression[i + 1] >= '0' && expression[i + 1] <= '9') return
      nums.push(val); val = 0
    } else {
      ops.push(ch)
    }
  })
  const m = ops.length
  if (m === 0) return [nums[0]]
  const calc = (x: number, y: number, op: string) => {
    switch (op) {
      case '+':return x + y
      case '-':return x - y
      case '*':return x * y
    }
    return -1
  }
  const dp: number[][][] = []
  for (let len = 1; len <= m; len++) {
    for (let i = 0; i + len - 1 < m; i++) {
      const j = i + len - 1
      dp[i] ??= []; dp[i][j] ??= []
      if (len === 1) dp[i][j].push(calc(nums[i], nums[i + 1], ops[i]))
      else {
        for (let k = i; k <= j; k++) {
          const a1 = k === i ? [nums[i]] : dp[i][k - 1]
          const a2 = k === j ? [nums[j + 1]] : dp[k + 1][j]
          for (const x of a1) {
            for (const y of a2) {
              dp[i][j].push(calc(x, y, ops[k]))
            }
          }
        }
      }
    }
  }
  return dp[0][m - 1]
};
