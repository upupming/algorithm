const s = []
const getS = () => {
  if (s.length) return
  const isPrime = (a) => {
    if (a === 1) return false
    for (let i = 2; i <= a / i; i++) {
      if (a % i === 0) return false
    }
    return true
  }
  for (let i = 1; i < 1e4; i++) {
    if (i < 10 && isPrime(i)) s.push(i)
Bg
    // 偶数长
    const a = Number(String(i) + String(i).split('').reverse().join(''))
    if (isPrime(a)) s.push(a)

    // 奇数长
    for (let j = 0; j < 10; j++) {
      const a = Number(String(i) + String(j) + String(i).split('').reverse().join(''))
      if (isPrime(a)) s.push(a)
    }
  }
  s.sort((a, b) => a - b)
}

function primePalindrome (n: number): number {
  getS()
  let l = 0; let r = s.length - 1
  // console.log(s[r])
  while (l < r) {
    const mid = l + r >> 1
    if (s[mid] >= n) r = mid
    else l = mid + 1
  }
  return s[l]
};
