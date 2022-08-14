/**
 * @param {number} n
 * @return {number}
 */
const numDupDigitsAtMostN = function (n) {
  let bits = []
  while (n) bits.push(n % 10), n = Math.floor(n / 10)
  bits = bits.reverse()

  const m = bits.length
  const cache = {}
  const dfs = (path = [], s = new Set(), alreadyLess = false) => {
    if (path.length === m) {
      return 0
    }
    let ans = 0
    const key = `${alreadyLess}_${path.length}_${[...s].sort((a, b) => a - b).join('_')}`
    if (cache[key] != null) return cache[key]
    for (let i = 0; i <= 9; i++) {
      const ok = alreadyLess || i <= bits[path.length]
      if (!ok) break
      const newAl = alreadyLess || i < bits[path.length]
      if (s.has(i)) {
        const rest = m - path.length - 1
        // 重复数字 i，并且前面已经保证小于，后面怎么填都无所谓了
        if (newAl) {
          ans += 10 ** rest
        }
        // 无法保证小于，后面填的必须完全小于等于
        else {
          if (rest === 0) ans += 1
          // 0~[xxx]
          else ans += Number(bits.slice(-rest).join('')) + 1
        }
        continue
      }

      path.push(i)
      let added = false
      // 前导 0 无需放入 set
      if (s.size === 0 && i === 0) {} else {
        s.add(i)
        added = true
      }
      ans += dfs(path, s, newAl)
      path.pop()
      if (added) s.delete(i)
    }
    // console.log(path, s, alreadyLess, ans)
    return cache[key] = ans
  }
  return dfs()
}
