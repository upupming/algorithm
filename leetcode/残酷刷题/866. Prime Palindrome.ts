function primePalindrome (n: number): number {
  const z: number[] = []
  for (let x = 1; x <= 2e4; x++) {
    const y: Array<number|string> = [
      String(x) + String(x).split('').reverse().join('')
    ]
    for (let i = 0; i < 10; i++) {
      y.push(String(x) + String(i) + String(x).split('').reverse().join(''))
    }
    if (x < 10) y.push(x)
    z.push(...y.map(Number))
  }

  z.sort((a, b) => a - b)
  for (const val of z) {
    if (isPrime(val) && val >= n) return val
  }
  return -1
  function isPrime (n: number): boolean {
    if (n === 1) return false
    for (let i = 2; i <= Math.sqrt(n); i++) {
      if (n % i === 0) return false
    }
    return true
  }
};
