/*
 * @lc app=leetcode id=802 lang=typescript
 *
 * [802] Find Eventual Safe States
 * 就是判断一个点是不是在环里面，在环里面的话会死循环，无法 terminal
 * 不在环里面的点经过拓扑排序可以得到，因此直接运行一遍拓扑排序即可
 * 注意需要将图的边反向一下，因为出度为 0 的点一定是安全的，去掉之后，再看出度为 0 的点一定是安全的，如此一层一层剥洋葱即可
 */

// @lc code=start
function eventualSafeNodes (graph: number[][]): number[] {
  const ans = []; const n = graph.length; const deg = Array(n).fill(0); const e: number[][] = Array(n).fill(0).map(() => [])
  for (let i = 0; i < n; i++) {
    deg[i] = graph[i].length
    for (const y of graph[i]) {
      e[y].push(i)
    }
  }
  const q: number[] = []
  for (let i = 0; i < n; i++) {
    if (deg[i] === 0) q.push(i)
  }
  while (q.length) {
    const x = q.shift()!
    ans.push(x)
    for (const y of e[x]) {
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }
  return ans.sort((a, b) => a - b)
};
// @lc code=end
