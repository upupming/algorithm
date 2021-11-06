/**
 * @param {number} numCourses
 * @param {number[][]} prerequisites
 * @return {boolean}
 */
const canFinish = function (numCourses, prerequisites) {
  const e = [...Array(numCourses)].map(() => []); const deg = Array(numCourses).fill(0)
  prerequisites.forEach(p => {
    e[p[1]].push(p[0])
    deg[p[0]]++
  })
  const q = []
  for (let i = 0; i < numCourses; i++) if (deg[i] === 0) q.push(i)
  let cnt = 0
  while (q.length) {
    const x = q.shift()
    cnt++
    for (const y of e[x]) {
      if (--deg[y] === 0) {
        q.push(y)
      }
    }
  }
  return cnt === numCourses
}
