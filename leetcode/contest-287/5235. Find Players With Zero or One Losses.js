/**
 * @param {number[][]} matches
 * @return {number[][]}
 */
const findWinners = function (m) {
  const p = new Set()
  const hl = new Set()
  const lc = {}
  for (const [w, l] of m) {
    p.add(w)
    p.add(l)
    lc[l] ??= 0
    lc[l]++
  }
  for (const [w, l] of m) {
    hl.add(l)
  }
  const nl = new Set()
  const eol = new Set()
  for (const x of p) {
    if (!hl.has(x)) nl.add(x)
    if (lc[x] === 1) eol.add(x)
  }
  return [[...nl].sort((a, b) => a - b), [...eol].sort((a, b) => a - b)]
}
