/**
 * @param {number[]} nums
 * @param {number[][]} edges
 * @return {number}
 */
const minimumScore = function (nums, edges) {
  const n = nums.length
  const e = Array(n).fill(0).map(() => [])
  for (const [x, y] of edges) {
    e[x].push(y)
    e[y].push(x)
  }
  let xAll = 0; let xBC, xA; let ret = 1e10
  for (const a of nums) xAll ^= a
  for (let i = 0; i < n; i++) {
    for (const j of e[i]) {
      // 删除边 i-j, j 所在的子树作为单调的一块
      // 计算以 i 为根，不含 j 的子树的异或和
      xBC = dfs(i, -1, j)
      xA = xAll ^ xBC
      // 在 B 中枚举第二条被删除的边
      dfs2(i, -1, j)
    }
  }
  return ret

  function dfs (x, fa, ban) {
    let ans = nums[x]
    for (const y of e[x]) {
      if (y !== fa && y !== ban) ans ^= dfs(y, x, ban)
    }
    return ans
  }
  function dfs2 (x, fa, ban) {
    let ans = nums[x]
    for (const y of e[x]) {
      if (y !== fa && y !== ban) {
        const xC = dfs2(y, x, ban)
        ans ^= xC
        const xB = xBC ^ xC
        ret = Math.min(ret, Math.max(xA, xB, xC) - Math.min(xA, xB, xC))
      }
    }
    return ans
  }
}
