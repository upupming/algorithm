/**
 * @param {number} n
 * @return {number}
 */
const nextBeautifulNumber = function (n) {
  const isBalance = (x) => {
    const cnt = Array(10).fill(0)
    String(x).split('').forEach(ch => {
      const d = ch.charCodeAt(0) - '0'.charCodeAt(0)
      cnt[d]++
    })
    for (let i = 0; i < 10; i++) {
      if (cnt[i] === 0 || cnt[i] === i) {} else return false
    }
    return true
  }
  while (++n) {
    if (isBalance(n)) return n
  }
}
