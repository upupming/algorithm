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
 * @param {number} startValue
 * @param {number} destValue
 * @return {string}
 */
const getDirections = function (root, startValue, destValue) {
  const findNode = (node, value, path = [], parents = []) => {
    if (!node) return
    if (node.val === value) return [node, path.slice(), [...parents, node.val]]
    path.push('L'), parents.push(node.val)
    let tmp = findNode(node.left, value, path, parents)
    path.pop()
    if (tmp) return tmp
    path.push('R')
    tmp = findNode(node.right, value, path, parents)
    path.pop(), parents.pop()
    return tmp
  }
  const [p, q] = [findNode(root, startValue), findNode(root, destValue)]
  const s = new Set(p[2])
  let lca = -1; let len = 0
  // console.log(q[2])
  while (q[2].length) {
    const tmp = q[2].pop()
    if (s.has(tmp)) {
      lca = tmp
      break
    }
    len++
  }
  let ans = ''
  // console.log(lca, p[2])
  for (let i = p[2].length - 1; i >= 0; i--) {
    if (p[2][i] === lca) break
    ans += 'U'
  }
  // console.log(len, q[1])
  ans += q[1].slice(q[1].length - len).join('')
  return ans
}
