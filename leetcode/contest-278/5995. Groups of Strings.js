/**
 * @param {string[]} words
 * @return {number[]}
 */
const groupStrings = function (w) {
  const n = w.length

  const map = {}

  const m = w.map((s, idx) => {
    let ans = 0
    for (const ch of s) {
      const j = ch.charCodeAt(0) - 'a'.charCodeAt(0)
      ans += 1 << j
    }
    map[ans] ??= []
    map[ans].push(idx)
    return ans
  })

  const fa = [...Array(n)].map((_, idx) => idx)
  const sz = Array(n).fill(1)
  function get (x) {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  function merge (x, y) {
    const fx = get(x); const fy = get(y)
    if (fx == fy) return
    if (sz[fx] < sz[fy]) {
      fa[fx] = fy
      sz[fy] += sz[fx]
    } else {
      fa[fy] = fx
      sz[fx] += sz[fy]
    }
  }

  for (const key of Object.keys(map)) {
    const vals = map[key]
    for (let i = 1; i < vals.length; i++) {
      merge(vals[i - 1], vals[i])
    }
  }

  for (let i = 0; i < n; i++) {
    const x = m[i]
    for (let j = 0; j < 26; j++) {
      // 设为 1
      const y = x | (1 << j)
      // 设为 0
      let z = x
      if (z >> j & 1) z -= 1 << j
      for (const val of [y, z]) {
        if (map[val]) {
          merge(map[val][0], i)
        }
      }

      if (x >> j & 1) {
        // 尝试将 j 位换成别的
        for (let k = 0; k < 26; k++) {
          if ((x >> k & 1) === 0) {
            const val = x - (1 << j) + (1 << k)
            if (map[val]) {
              if (map[val]) {
                merge(map[val][0], i)
              }
            }
          }
        }
      }
    }
  }

  const ans = []; let max = 0
  for (let i = 0; i < n; i++) {
    if (get(i) === i) ans.push(i), max = Math.max(sz[i], max)
  }
  return [ans.length, max]
}
