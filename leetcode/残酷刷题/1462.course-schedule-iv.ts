/*
 * @lc app=leetcode id=1462 lang=typescript
 * 拓扑排序，维护一下前驱即可
 * [1462] Course Schedule IV
 */

// @lc code=start
function checkIfPrerequisite (numCourses: number, prerequisites: number[][], queries: number[][]): boolean[] {
  const pre = Array(numCourses).fill(0).map(() => new Set<number>())
  const deg = Array(numCourses).fill(0)
  const e: number[][] = Array(numCourses).fill(0).map(() => [])
  for (const p of prerequisites) {
    deg[p[1]]++
    e[p[0]].push(p[1])
  }

  const q: number[] = []
  for (let i = 0; i < numCourses; i++) {
    if (deg[i] === 0) q.push(i)
  }
  while (q.length) {
    const x = q.shift()!
    for (const y of e[x]) {
      pre[y].add(x)
      pre[x].forEach(pre[y].add, pre[y])
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }

  const ans: boolean[] = []
  for (const q of queries) {
    ans.push(pre[q[1]].has(q[0]))
  }
  return ans
};
// @lc code=end
