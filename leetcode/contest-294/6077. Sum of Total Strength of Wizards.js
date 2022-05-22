/**
 * @param {number[]} strength
 * @return {number}
 */
const totalStrength = function (s) {
  const n = s.length
  s.unshift(-1), s.push(-1)
  const sum = [0]; const ss = [0]; const P = 1e9 + 7; const Pn = BigInt(1e9 + 7)
  for (let i = 1; i <= n; i++) sum[i] = (sum[i - 1] + s[i]) % P
  for (let i = 1; i <= n; i++) ss[i] = (ss[i - 1] + sum[i]) % P
  const L = []; const R = []; let stk = [0]
  for (let i = 1; i <= n; i++) {
    while (s[stk[stk.length - 1]] >= s[i]) stk.pop()
    L[i] = stk[stk.length - 1] + 1
    stk.push(i)
  }
  stk = [n + 1]
  for (let i = n; i >= 1; i--) {
    while (s[stk[stk.length - 1]] > s[i]) stk.pop()
    R[i] = stk[stk.length - 1] - 1
    stk.push(i)
  }
  let ans = 0n

  for (let i = 1; i <= n; i++) {
    const tmp = BigInt(i - L[i] + 1) * BigInt((ss[R[i]] - ss[i - 1] + P) % P) % Pn - BigInt(R[i] - i + 1) * BigInt((ss[i - 1] - (ss[L[i] - 2] ?? 0) + P) % P) % Pn + Pn
    ans = (ans + tmp * BigInt(s[i])) % Pn
  }

  return ans
}
