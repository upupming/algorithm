function superpalindromesInRange (left: string, right: string): number {
  const [l, r] = [left, right].map(BigInt)
  const z = new Set<BigInt>()
  function isPalindrome (y: bigint) {
    return String(y) === String(y).split('').reverse().join('')
  }
  function add (x: bigint) {
    const y = x * x
    if (y >= l && y <= r && isPalindrome(y)) {
      z.add(y)
    }
  }
  for (let x = 1n; x <= Math.sqrt(Math.sqrt(Number(right))) + 100; x++) {
    if (x < 10) add(x)
    add(BigInt(String(x) + String(x).split('').reverse().join('')))
    for (let i = 0; i < 10; i++) {
      add(BigInt(String(x) + String(i) + String(x).split('').reverse().join('')))
    }
  }
  return z.size
};
