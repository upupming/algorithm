/**
 * @param {number} n
 * @return {number}
 */
const countSpecialNumbers = function (n) {
  let bits = []
  while (n) bits.push(n % 10), n = Math.floor(n / 10)
  bits = bits.reverse()
  const m = bits.length
  const cache = {}
  const dfs = (path = [], s = new Set(), alreadyLess = false) => {
    let ans = 0
    if (path.length === m) {
      if (!s.size) {} else ans++
      return ans
    }
    const key = `${path.length}@${[...s].sort((a, b) => a - b).join('_')}`
    if (cache[key] != null && alreadyLess) {
      return cache[key]
    }
    for (let i = 0; i <= 9; i++) {
      if (s.has(i)) {
        continue
      }
      if (alreadyLess || (i <= bits[path.length])) {
        const newAl = alreadyLess || (i < bits[path.length])
        let added = false
        path.push(i)
        if (s.size > 0 || (i !== 0)) {
          s.add(i)
          added = true
        }
        ans += dfs(path, s, newAl)
        path.pop()
        if (added) {
          s.delete(i)
        }
      }
    }
    return cache[key] = ans
  }
  return dfs()
}
