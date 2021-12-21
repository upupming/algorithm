const lowestCommonAncestor = function (root, p, q) {
  const f = new Map(); const d = new Map()
  const t = 20
  const bfs = () => {
    f.set(root, Array(t + 1).fill(root))
    const q = [root]
    d.set(root, 1)
    while (q.length) {
      const x = q.pop()
      for (const y of [x.left, x.right]) {
        if (!y) continue
        d.set(y, d.get(x) + 1)
        // console.log(x.val, y.val, d[x], d[y])
        const fy = []
        fy[0] = x
        for (let j = 1; j <= t; j++) {
          fy[j] = f.get(fy[j - 1])[j - 1]
        }
        f.set(y, fy)
        q.push(y)
      }
    }
  }
  const lca = (p, q) => {
    // d[p] <= d[q], q 向上调整
    if (d.get(p) > d.get(q)) [p, q] = [q, p]
    for (let i = t; i >= 0; i--) {
      if (d.get(f.get(q)[i]) >= d.get(p)) q = f.get(q)[i]
    }
    if (p === q) return p
    for (let i = t; i >= 0; i--) {
      if (f.get(p)[i] !== f.get(q)[i]) p = f.get(p)[i], q = f.get(q)[i]
    }
    return f.get(p)[0]
  }
  bfs()
  return lca(p, q)
}

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
const lcaDeepestLeaves = function (root) {
  const getDepth = (node) => {
    if (!node) return 0
    return Math.max(getDepth(node.left), getDepth(node.right)) + 1
  }
  const depth = getDepth(root)
  const deepestLeaves = []
  const dfs = (node, d = 1) => {
    if (!node) return
    if (!node.left && !node.right) {
      if (d === depth) deepestLeaves.push(node)
      return
    }
    dfs(node.left, d + 1)
    dfs(node.right, d + 1)
  }
  dfs(root)
  while (deepestLeaves.length > 1) {
    const [a, b] = [deepestLeaves.pop(), deepestLeaves.pop()]
    deepestLeaves.push(lowestCommonAncestor(root, a, b))
  }
  return deepestLeaves[0]
}
