/**
 * @param {string} s
 * @param {number[]} answers
 * @return {number}
 */
// 暴力 TLE
const scoreOfStudents = function (s, answers) {
  let val = 0; const n = s.length
  const nums = []; const ops = []; const stk = []; const a = []
  for (let i = 0; i < n; i++) {
    if (s.charCodeAt(i) >= '0'.charCodeAt(0) && s.charCodeAt(i) <= '9'.charCodeAt(0)) {
      val = val * 10 + (s.charCodeAt(i) - '0'.charCodeAt(0))
      if (i + 1 < n && s.charCodeAt(i + 1) >= '0'.charCodeAt(0) && s.charCodeAt(i + 1) <= '9'.charCodeAt(0)) continue
      a.push(val), nums.push(val), val = 0
    } else {
      stk.push(s[i])
      while (ops.length && grade(ops[ops.length - 1]) >= grade(s[i])) {
        const op = ops.pop()
        const y = nums.pop(); const x = nums.pop()
        nums.push(op === '*' ? x * y : x + y)
      }
      ops.push(s[i])
    }
  }
  while (ops.length && nums.length >= 2) {
    const op = ops.pop()
    const y = nums.pop(); const x = nums.pop()
    nums.push(op === '*' ? x * y : x + y)
  }
  const correct = nums[0]
  function grade (op) {
    switch (op) {
      case '*': return 3
      case '+': return 2
    }
    return 0
  }

  const m = stk.length
  const calc = (x, y, op) => {
    return op === '*' ? (x * y) : (x + y)
  }
  const dp = [...Array(m + 1)].map(() => [])
  for (let len = 1; len <= m; len++) {
    for (let i = 0; i + len - 1 < m; i++) {
      const j = i + len - 1
      if (len === 1) {
        dp[i][j] = new Set([calc(a[i], a[i + 1], stk[i])])
        continue
      }
      const s = new Set()
      for (let k = i; k <= j; k++) {
        const sx = k === i ? [a[i]] : dp[i][k - 1]
        const sy = k === j ? [a[j + 1]] : dp[k + 1][j]
        for (const x of sx) {
          for (const y of sy) {
            const b = calc(x, y, stk[k])
            if (b <= 1000) s.add(b)
          }
        }
      }
      // console.log(i, j, s)
      dp[i][j] = s
    }
  }

  const p = dp[0][m - 1]

  // console.log(correct, p)
  let ans = 0
  for (const as of answers) {
    if (as === correct) ans += 5
    else if (p.has(as)) ans += 2
  }
  return ans
  // console.log(p)
}
