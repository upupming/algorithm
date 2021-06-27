function largestPalindrome (n: number): number {
  if (n === 1) return 9
  const [low, high] = [Math.pow(10, n - 1), Math.pow(10, n) - 1].map(BigInt)
  for (let x = high; x >= low; x--) {
    const y = BigInt(String(x) + String(x).split('').reverse().join(''))
    for (let a = high; a >= Math.sqrt(Number(y)); a--) {
      if (y % a === 0n && y / a >= low) {
        return Number(y % 1337n)
      }
    }
  }
  return -1
};
