/*
 * @lc app=leetcode id=48 lang=typescript
 *
 * [48] Rotate Image
 * 转置 + 左右列对换
 */

// @lc code=start
/**
 Do not return anything, modify matrix in-place instead.
 */
function rotate (matrix: number[][]): void {
  const n = matrix.length
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < i; j++) {
      [matrix[i][j], matrix[j][i]] = [matrix[j][i], matrix[i][j]]
    }
  }
  for (let i = 0; i < n; i++) {
    for (let j = 0, k = n - 1; j < k; j++, k--) {
      [matrix[i][j], matrix[i][k]] = [matrix[i][k], matrix[i][j]]
    }
  }
};
// @lc code=end
