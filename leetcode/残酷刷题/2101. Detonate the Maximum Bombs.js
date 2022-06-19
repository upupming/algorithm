/**
 * @param {number[][]} bombs
 * @return {number}
 */
 var maximumDetonation = function(bs) {
  const n = bs.length
  const e = Array(n).fill(0).map(() => [])
  for (let i = 0; i < n; i++) {
      for (let j = 0; j < n; j++) {
          // i 可以引爆 j
          if ((bs[i][0] - bs[j][0])**2 + (bs[i][1] - bs[j][1])**2 <= bs[i][2] ** 2) {
              e[i].push(j)
          }
      }
  }
  let ans = 0
  for (let i = 0; i < n; i++) {
      const v = Array(n).fill(0)
      v[i] = 1
      const q = [i]
      while (q.length) {
          const cur = q.shift()
          for (const y of e[cur]) {
              if (v[y]) continue
              v[y] = 1
              q.push(y)
          }
      }
      ans = Math.max(ans, v.reduce((p, c) => p+c, 0))
  }
  return ans
};
