/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     val: number
 *     left: TreeNode | null
 *     right: TreeNode | null
 *     constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.left = (left===undefined ? null : left)
 *         this.right = (right===undefined ? null : right)
 *     }
 * }
 */
function canMerge (trees: Array<TreeNode | null>): TreeNode | null {
  const roots = new Map<number, TreeNode>()
  const leaves = new Set<number>()
  for (const tree of trees) {
    roots.set(tree.val, tree)
    if (tree.left) {
      leaves.add(tree.left.val)
    }
    if (tree.right) {
      leaves.add(tree.right.val)
    }
  }
  // 根节点一定是在 roots 中但是不在 leaves 中的点
  let rootVal = -1
  for (const [val] of roots) {
    if (!leaves.has(val)) {
      if (rootVal === -1) {
        rootVal = val
      }
      // 有两个根节点，无法合并在一起
      else {
        return null
      }
    }
  }
  let ok = true
  const root = dfs(rootVal)
  return (ok && roots.size === 0) ? root : null
  function dfs (val: number, min: number = -1, max: number = 1e5): TreeNode | null {
    const tree = roots.get(val)
    roots.delete(val)
    if (!tree) return null
    if (tree.left) {
      tree.left = dfs(tree.left.val, min, tree.val) || tree.left
      if (tree.left?.val >= tree.val || tree.left?.val <= min) {
        ok = false
        return null
      }
    }
    if (tree.right) {
      tree.right = dfs(tree.right.val, tree.val, max) || tree.right
      if (tree.right?.val >= max || tree.right?.val <= tree.val) {
        ok = false
        return null
      }
    }
    return tree
  }
};
