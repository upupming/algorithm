/**
 * @param {string} pattern
 * @return {string}
 */
const smallestNumber = function (p) {
  let ans = 1e10
  const n = p.length
  const valid = (x, y, pt) => {
    if (pt === 'I') {
      return x < y
    } else {
      return x > y
    }
  }
  const dfs = (path = [], s = new Set()) => {
    if (path.length === n + 1) {
      ans = Math.min(ans, Number(path.join('')))
      return
    }
    for (let i = 1; i <= 9; i++) {
      if (s.has(i)) continue
      if (path.length === 0 || valid(path[path.length - 1], i, p[path.length - 1])) {
        path.push(i), s.add(i)
        dfs(path, s)
        path.pop(), s.delete(i)
      }
    }
  }
  dfs()
  return String(ans)
}
