/**
 * @param {number} n
 * @return {number}
 */
const findIntegers = function (n) {
  let bits = []
  const n1 = n
  while (n) bits.push(n % 2), n = Math.floor(n / 2)
  bits = bits.reverse()
  const m = bits.length
  const cache = {}
  // 出现了连续的1的数的个数
  const dfs = (path = [], alreadyLess = false) => {
    if (path.length === m) {
      return 0
    }
    let ans = 0
    const key = `${alreadyLess}_${path.length}_${path[path.length - 1]}`
    if (cache[key] != null) return cache[key]
    for (let i = 0; i <= 1; i++) {
      const ok = alreadyLess || i <= bits[path.length]
      if (!ok) break
      const newAl = alreadyLess || i < bits[path.length]

      if (path.length && path[path.length - 1] === 1 && i === 1) {
        const rest = m - path.length - 1
        // 出现了连续的 1，并且前面已经保证小于，后面怎么填都无所谓了
        if (newAl) {
          ans += 2 ** rest
        }
        // 无法保证小于，后面填的必须完全小于等于
        else {
          if (rest === 0) ans += 1
          // 0~[xxx]
          else ans += parseInt(bits.slice(-rest).join(''), 2) + 1
        }
        continue
      }

      path.push(i)
      ans += dfs(path, newAl)
      path.pop()
    }
    return cache[key] = ans
  }
  return n1 + 1 - dfs()
}
