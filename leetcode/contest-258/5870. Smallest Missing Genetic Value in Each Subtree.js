/**
 * @param {number[]} parents
 * @param {number[]} nums
 * @return {number[]}
 */
const smallestMissingValueSubtree = function (parents, nums) {
  const n = parents.length
  const adj = [...Array(n)].map(() => []); const mex = Array(n).fill(1)
  for (let i = 1; i < parents.length; i++) {
    adj[parents[i]].push(i)
  }
  const mp = [...Array(n)].map(() => new Set())
  dfs(0)
  return mex
  function dfs (u) {
    for (const v of adj[u]) {
      dfs(v)
      // 如果 mex[v] 大于 mex[u] 说明 v 的子集中不缺 mex[u]，所以取最大值就行了
      mex[u] = Math.max(mex[u], mex[v])
      if (mp[v].size > mp[u].size) {
        [mp[v], mp[u]] = [mp[u], mp[v]]
      }
      for (const x of mp[v]) mp[u].add(x)
    }
    mp[u].add(nums[u])
    while (mp[u].has(mex[u])) mex[u]++
  }
}
