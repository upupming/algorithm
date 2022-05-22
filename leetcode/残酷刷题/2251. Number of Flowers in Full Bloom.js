/**
 * @param {number[][]} flowers
 * @param {number[]} persons
 * @return {number[]}
 */
const fullBloomFlowers = function (f, p) {
  const l = []; const l2i = {}
  for (const [s, e] of f) {
    l.push(s, e + 1)
  }
  l.sort((a, b) => a - b)
  for (let i = 0; i < l.length; i++) l2i[l[i]] = i
  const diff = Array(l.length).fill(0)
  for (const [s, e] of f) {
    diff[l2i[s]] += 1
    diff[l2i[e + 1]] -= 1
  }
  let cur = 0; let i = 0; const ans = []
  p.map((x, idx) => [x, idx])
    .sort((a, b) => a[0] - b[0])
    .forEach(([x, idx]) => {
      while (l[i] <= x) cur += diff[i++]
      ans[idx] = cur
    })
  return ans
}
