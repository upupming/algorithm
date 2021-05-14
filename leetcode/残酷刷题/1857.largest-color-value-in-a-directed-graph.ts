/*
 * @lc app=leetcode id=1857 lang=typescript
 *
 * [1857] Largest Color Value in a Directed Graph
 */

// @lc code=start
const _max = Math.max.bind(Math)

// eslint-disable-next-line @typescript-eslint/no-unused-vars
function largestPathValue (colors: string, edges: number[][]): number {
  const n = colors.length

  const e: number[][] = Array(n).fill(0).map(() => []); const deg = Array(n).fill(0)
  for (const edge of edges) {
    e[edge[0]].push(edge[1])
    deg[edge[1]]++
  }

  const value: number[][] = Array(n).fill(0).map(() => Array(26).fill(0))

  const topsort = () => {
    const q: number[] = []
    for (let i = 0; i < n; i++) {
      if (deg[i] === 0) q.push(i)
    }
    let cnt = 0
    while (q.length) {
      const x = q[0]
      q.shift()
      // 加上自己的颜色
      value[x][colors[x].charCodeAt(0) - 'a'.charCodeAt(0)] += 1
      cnt++
      for (const y of e[x]) {
        for (let i = 0; i < 26; i++) {
          // 找到最优的前驱 x
          value[y][i] = _max(value[y][i], value[x][i])
        }
        if (--deg[y] === 0) q.push(y)
      }
    }
    return cnt === n
  }

  if (!topsort()) return -1

  let ans = 0
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < 26; j++) {
      ans = _max(ans, value[i][j])
    }
  }
  return ans
};
// @lc code=end
