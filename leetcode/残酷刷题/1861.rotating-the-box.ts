/*
 * @lc app=leetcode id=1861 lang=typescript
 *
 * [1861] Rotating the Box
 * 对于每一列，自下到上考虑，记录一下最下面可以到达的地方，遇到石子的时候将石子放到最下面可以到达的地方，然后更新情况
 */

// @lc code=start
function rotateTheBox (box: string[][]): string[][] {
  const [n, m] = [box.length, box[0].length]
  const ans = Array(m).fill(0).map(() => Array(n).fill(0))
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      ans[i][j] = box[n - 1 - j][i]
    }
  }
  for (let j = 0; j < n; j++) {
    let hole = -1
    for (let i = m - 1; i >= 0; i--) {
      if (ans[i][j] === '#' && hole !== -1) {
        ans[hole][j] = '#'
        ans[i][j] = '.'
        hole--
      } else if (ans[i][j] === '*') {
        hole = -1
      } else if (ans[i][j] === '.') {
        if (hole === -1) hole = i
      }
    }
  }
  return ans
};
// @lc code=end
