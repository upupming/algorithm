/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number}
 */
const maxPathSum = function (root) {
  let ans = -1e10
  const dfs = (p) => {
    if (p === null) return 0
    const l = dfs(p.left); const r = dfs(p.right)
    ans = Math.max(ans, Math.max(l + p.val, r + p.val, l + r + p.val))
    return Math.max(0, l + p.val, r + p.val)
  }
  dfs(root)
  return ans
}
