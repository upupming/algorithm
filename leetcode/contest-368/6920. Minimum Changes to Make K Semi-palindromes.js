/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
const minimumChanges = function (s, k) {
  const n = s.length; const N = 201
  const modify = Array(n).fill(0).map(() => Array(n).fill(0))
  const divisors = []
  for (let i = 1; i < N; i++) {
    for (let j = i * 2; j < N; j += i) {
      if (divisors[j] == undefined) {
        divisors[j] = []
      }
      divisors[j].push(i)
    }
  }

  const getModify = (s) => {
    let ans = 1e10
    for (const d of divisors[s.length]) {
      let cnt = 0
      for (let i = 0; i < d; i++) {
        let t = ''
        for (let j = i; j < s.length; j += d) {
          t += s[j]
        }
        for (let i = 0; i < t.length / 2; i++) {
          if (t[i] != t[t.length - i - 1]) {
            cnt++
          }
        }
      }
      ans = Math.min(ans, cnt)
    }
    return ans
  }
  for (let i = 0; i < n - 1; i++) {
    for (let j = i + 1; j < n; j++) {
      modify[i][j] = getModify(s.slice(i, j + 1))
    }
  }

  const cache = {}
  const dfs = (i, j) => {
    if (cache[`[${i},${j}]`] != undefined) {
      return cache[`[${i},${j}]`]
    }
    if (j === 0) return modify[i][n - 1]
    let ans = 1e10
    for (let r = i + 1; r < n - j * 2; r++) {
      ans = Math.min(ans, modify[i][r] + dfs(r + 1, j - 1))
    }
    return cache[`[${i},${j}]`] = ans
  }
  return dfs(0, k - 1)
}
