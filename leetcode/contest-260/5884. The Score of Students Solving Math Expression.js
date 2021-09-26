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

  const p = new Set()
  // let cnt = 0
  dfs(a, stk)
  function dfs (a, stk) {
    // if (cnt % 1e3 === 0) { console.log(cnt) }
    // console.log(a, stk)
    if (stk.length === 0) {
      p.add(a[0])
      return
    }
    const calc = (x, y, op) => {
      // console.log(x, y, op, op === '*' ? x * y : x + y)
      return op === '*' ? x * y : x + y
    }
    for (let i = 0; i < stk.length; i++) {
      const op = stk[i]
      const tmp = calc(a[i], a[i + 1], op)
      if (tmp > 1000 || tmp === 0) continue
      dfs(
        [...a.slice(0, i), tmp, ...a.slice(i + 2)],
        [...stk.slice(0, i), ...stk.slice(i + 1)]
      )
    }
  }

  // console.log(correct, p)
  let ans = 0
  for (const as of answers) {
    if (as === correct) ans += 5
    else if (p.has(as)) ans += 2
  }
  return ans
  // console.log(p)
}
