/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
const circularGameLosers = function (n, k) {
  const s = new Set(); let cur = 1; let j = 1
  while (true) {
    if (s.has(cur)) break
    s.add(cur)
    cur = ((cur + k * (j++) - 1) % n) + 1
  }
  const ans = []
  for (let i = 1; i <= n; i++) {
    if (!s.has(i)) ans.push(i)
  }
  return ans
}
