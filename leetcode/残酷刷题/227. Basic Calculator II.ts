function calculate (s: string): number {
  let val = 0; const n = s.length
  const nums: number[] = []; const ops: string[] = []
  s.split('').forEach((ch, i) => {
    if (ch === ' ') return
    if (ch >= '0' && ch <= '9') {
      val = val * 10 + ch.charCodeAt(0) - '0'.charCodeAt(0)
      if (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') return
      nums.push(val)
      val = 0
    } else if (ch === '(') {
      ops.push('(')
    } else if (ch === ')') {
      while (ops.length && ops[ops.length - 1] !== '(') {
        calc(ops.pop()!)
      }
      if (ops.length) ops.pop()
    } else {
      while (ops.length && grade(ops[ops.length - 1]) >= grade(ch)) {
        calc(ops.pop()!)
      }
      ops.push(ch)
    }
  })
  while (ops.length) {
    calc(ops.pop()!)
  }
  return nums[0]

  function grade (op: string) {
    switch (op) {
      case '+':
      case '-':
        return 1
      case '*':
      case '/':
        return 2
    }
    return -1
  }
  function calc (op: string) {
    const [y, x] = [nums.pop()!, nums.pop()!]
    let z = 0
    switch (op) {
      case '+':
        z = x + y
        break
      case '-':
        z = x - y
        break
      case '*':
        z = x * y
        break
      case '/':
        z = Math.floor(x / y)
        break
    }
    nums.push(z)
  }
};
