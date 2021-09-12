/**
 * @param {number[][]} rectangles
 * @return {number}
 */
 var interchangeableRectangles = function(rectangles) {
  const P = 1e5 + 7
  const mp = (i, j) => i * P + j
  const gcd = (a, b) => b ? gcd(b, a % b) : a
  const map = {}
  rectangles.forEach(r => {
      const [w, h] = r
      const d = gcd(w, h)
      let idx = mp(w/d, h/d)
      map[idx] ??= 0
      map[idx] += 1
  })
  let ans = 0
  for (let c of Object.values(map)) {
      ans += (c - 1) * c / 2
  }
  return ans
};
