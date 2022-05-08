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
 var averageOfSubtree = function(root) {
  let ans = 0
  const dfs = (node) => {
      if (!node) return [0, 0]
      let [l, lCnt] = dfs(node.left)
      let [r, rCnt] = dfs(node.right)
      let sum = (l+r+node.val), cnt = lCnt+rCnt+1
      if (Math.floor(sum / cnt) === node.val) ans++
      return [sum, cnt]
  }
  dfs(root)
  return ans
};
