function shortestPalindrome (s: string): string {
  const [P, Q] = [131, 1e9 + 7]
  const [p, f] = [[1], [0]]
  const n = s.length
  for (let i = 0; i < n; i++) {
    f[i + 1] = (f[i] * P + (s[i].charCodeAt(0) - 'a'.charCodeAt(0) + 1)) % Q
    p[i + 1] = P * p[i] % Q
  }
  function getHash (l: number, r: number) {
    return (f[r] - f[l - 1] * p[r - l + 1] % Q + Q) % Q
  }
  let [h, maxLen] = [0, 0]
  for (let i = 0; i < n; i++) {
    h = (((s[i].charCodeAt(0) - 'a'.charCodeAt(0) + 1) * p[i] % Q) + h) % Q
    if (h === getHash(1, i + 1)) maxLen = i + 1
  }
  console.log(maxLen)
  return s.slice(maxLen).split('').reverse().join('') + s
};
