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
const longestUnivaluePath = function (root) {
  let ans = 0
  const dfs = (p) => {
    if (p === null) return 0
    const l = dfs(p.left); const r = dfs(p.right)
    let ret = 0; let tmp = 0
    if (p.left?.val === p.val) ret = Math.max(ret, l), tmp += l
    if (p.right?.val === p.val) ret = Math.max(ret, r), tmp += r
    ans = Math.max(ans, tmp)
    // 返回经过在 p 点结束的最长路径节点个数
    return ret + 1
  }
  dfs(root)
  return ans
}
