function minCharacters (a: string, b: string): number {
  const A = a.split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0))
  const B = b.split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0))
  let ans = 1e6
  work(A, B)
  work(B, A)

  // a == x, b = x
  for (let x = 0; x < 26; x++) {
    const tmp = A.reduce((acc, cur) => acc + (cur !== x ? 1 : 0), 0) +
              B.reduce((acc, cur) => acc + (cur !== x ? 1 : 0), 0)
    ans = Math.min(ans, tmp)
  }

  return ans

  function work (A: number[], B: number[]) {
    // a <= x, b > x
    for (let x = 0; x < 26 - 1; x++) {
      const tmp = A.reduce((acc, cur) => acc + (cur > x ? 1 : 0), 0) +
                B.reduce((acc, cur) => acc + (cur <= x ? 1 : 0), 0)
      ans = Math.min(ans, tmp)
    }
  }
};
