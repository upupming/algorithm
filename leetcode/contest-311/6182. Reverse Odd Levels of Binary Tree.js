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
 * @return {TreeNode}
 */
const reverseOddLevels = function (root) {
  let q = [[root, 0]]
  const a = []; let idx = 0
  while (q.length) {
    const [node, dep] = q.pop()
    a.push(node.val)
    if (node.right) q.push([node.right, dep + 1])
    if (node.left) q.push([node.left, dep + 1])
  }
  q = [[root, 0]]
  while (q.length) {
    const [node, dep] = q.pop()
    if (dep % 2 === 1) node.val = a[idx]
    idx++
    if (node.left) q.push([node.left, dep + 1])
    if (node.right) q.push([node.right, dep + 1])
  }
  return root
}
