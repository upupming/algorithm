/**
 * @param {number[]} edges
 * @return {number}
 */
const edgeScore = function (edges) {
  const n = edges.length
  let s = Array(n).fill(0)
  for (let i = 0; i < n; i++) {
    s[edges[i]] += i
  }
  s = s.map((x, idx) => [x, idx]).sort((a, b) => {
    if (a[0] === b[0]) return a[1] - b[1]
    return b[0] - a[0]
  })
  return s[0][1]
}
