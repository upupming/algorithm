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
 * @param {number[]} queries
 * @return {number[]}
 */
const treeQueries = function (root, queries) {
  const map = {}

  const num_ch = (node) => {
    let cnt = 0
    if (node.left) cnt++
    if (node.right) cnt++
    return cnt
  }
  const dfs = (node, p = null) => {
    if (node == null) return
    map[node.val] = node
    if (p && num_ch(p) === 1) node.lp = p.lp, node.lpn = p.lpn + 1
    else node.lp = node, node.lpn = 0
    // console.log(node.val, node.lp?.val)
    dfs(node.left, node)
    dfs(node.right, node)
    node.height = Math.max(node.left?.height ?? 0, node.right?.height ?? 0) + 1
    node.parent = p
  }
  root.lp = root
  root.lpn = 0
  dfs(root)

  const ans = []
  for (const q of queries) {
    let node = map[q].lp
    node.newHeight = map[q].lpn
    // console.log(node, node.newHeight)
    while (node && node.parent) {
      const p = node.parent
      let sible = null
      for (const x of [p.left, p.right]) if (x !== node) sible = x
      p.newHeight = Math.max(node.newHeight, sible?.height ?? 0) + 1

      // console.log(node.val, node.newHeight, sible?.val, sible?.height, p.val, p.newHeight)
      node = p
    }
    ans.push(root.newHeight - 1)
  }
  return ans
}
