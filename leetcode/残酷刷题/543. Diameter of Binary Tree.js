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
 var diameterOfBinaryTree = function(root) {
  let ans = 0
  const dfs = (p) => {
      if (p === null) return 0
      const l = dfs(p.left)
      const r = dfs(p.right)
      // 经过当前点的答案
      ans = Math.max(ans, l + r)
      // 当前点左或右链的最大长度
      return Math.max(l, r) + 1
  }
  dfs(root)
  return ans
};
