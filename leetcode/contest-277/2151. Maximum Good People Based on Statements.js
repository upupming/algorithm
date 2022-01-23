/**
 * @param {number[][]} statements
 * @return {number}
 */
const maximumGood = function (s) {
  const n = s.length
  let ans = 0
  for (let i = 0; i < 1 << n; i++) {
    const good = []
    const set = (j, x) => {
      if (good[j] != null && good[j] !== x) return false
      good[j] = x
      return true
    }
    let ok = true
    for (let j = 0; j < n; j++) {
      if (i >> j & 1) {
        ok = set(j, 1)
        // 所有话都是真的
        for (let k = 0; k < n; k++) {
          if (s[j][k] === 2) continue
          ok &&= set(k, s[j][k])
        }
      }
      // j 是 B
      else {
        ok = set(j, 0)
      }
      if (ok == false) break
    }
    if (ok) {
      let cnt = 0
      for (let i = 0; i < n; i++) {
        cnt += good[i] === 1
      }
      ans = Math.max(ans, cnt)
    }
  }
  return ans
}
/*
[[2,0,2,2,0],[2,2,2,1,2],[2,2,2,1,2],[1,2,0,2,2],[1,0,2,1,2]]
[[2,1,0,0,2],[2,2,1,0,2],[0,2,2,1,0],[2,0,0,2,0],[2,0,0,1,2]]
*/
