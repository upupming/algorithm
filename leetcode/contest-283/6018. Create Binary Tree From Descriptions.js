/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {number[][]} descriptions
 * @return {TreeNode}
 */
const createBinaryTree = function (d) {
  const map = {}
  const numP = {}
  for (const xx of d) {
    const [p, x, l] = xx
    map[x] ??= new TreeNode(x, null, null)
    map[p] ??= new TreeNode(p, null, null)
    if (l) map[p].left = map[x]
    else map[p].right = map[x]
    numP[x] ??= 0
    numP[x]++
  }
  for (const [key, val] of Object.entries(map)) {
    if (!numP[key]) return val
  }
}
