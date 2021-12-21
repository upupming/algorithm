/**
 * Definition for a binary tree node.
 * function TreeNode(target) {
 *     this.val = target;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {TreeNode}
 */
const lowestCommonAncestor_bf = function (root, p, q) {
  const findNode = (node, target, path = []) => {
    if (!node) return
    path.push(node)
    if (node.val === target.val) return [node, path.slice()]
    let tmp = findNode(node.left, target, path)
    if (tmp) return tmp
    tmp = findNode(node.right, target, path)
    if (tmp) return tmp
    path.pop()
  }
  const [nodeP, p1] = findNode(root, p)
  const s = new Set(p1.map(n => n.val))
  const [nodeQ, p2] = findNode(root, q)
  while (p2.length) {
    const tmp = p2.pop()
    if (s.has(tmp.val)) {
      return tmp
    }
  }
}

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
