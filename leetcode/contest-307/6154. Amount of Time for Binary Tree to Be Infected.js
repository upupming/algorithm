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
 * @param {number} start
 * @return {number}
 */
const amountOfTime = function (root, start) {
  const n = 0

  const e = {}
  const dfs1 = (node) => {
    if (!node) return
    const x = node.val
    const l = node.left?.val
    const r = node.right?.val
    e[x] ??= []
    if (l != null) {
      e[l] ??= []
      e[x].push(l)
      e[l].push(x)
    }
    if (r != null) {
      e[r] ??= []
      e[x].push(r)
      e[r].push(x)
    }
    dfs1(node.left)
    dfs1(node.right)
  }
  dfs1(root)

  const q = [start]
  const d = {}
  d[start] = 0
  let ans = 0
  // console.log(mp)
  // console.log(e)
  while (q.length) {
    const x = q.shift()
    // console.log(x, e[x])
    for (const y of e[x]) {
      if (d[y] != null) continue
      d[y] = d[x] + 1
      // console.log(y, d[y])
      ans = Math.max(ans, d[y])
      q.push(y)
    }
  }
  return ans
}
