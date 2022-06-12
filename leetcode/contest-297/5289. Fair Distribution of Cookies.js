/**
 * @param {number[]} cookies
 * @param {number} k
 * @return {number}
 */
 var distributeCookies = function(ck, k) {
  let ans = 1e10
  const n = ck.length
  const dfs = (x, s) => {
      let max = Math.max(...s)
      if (max >= ans) return
      if (x === n) {
          ans = Math.min(ans, max)
          return
      }
      for (let i = 0; i < k; i++) {
          s[i] += ck[x]
          dfs(x+1, s)
          s[i] -= ck[x]
      }
  }
  dfs(0, Array(k).fill(0))
  return ans
};
