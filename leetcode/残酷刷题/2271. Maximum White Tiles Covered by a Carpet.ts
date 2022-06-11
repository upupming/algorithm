function maximumWhiteTiles (tiles: number[][], carpetLen: number): number {
  const tree = new SegmentTree(0, 1e9)
  for (const [l, r] of tiles) {
    tree.modifyRange(l, r, 1)
  }
  let ans = 0
  for (const [l, r] of tiles) {
    const { sum } = tree.query(l, Math.min(l + carpetLen - 1, 1e9))
    ans = Math.max(ans, sum)
  }
  return ans
};

export declare const a: 1

class Node {
  start: number
  end: number
  max: number = 0
  sum: number = 0
  lazy: number | null = null
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (pos: number, val: number) {
    this.modifyNode(this.root, pos, val)
  }

  modifyNode (node: Node, pos: number, val: number) {
    if (node.start === pos && node.end === pos) {
      node.max = node.sum = val
    } else {
      this.pushdown(node)
      if (pos <= node.left!.end) this.modifyNode(node.left!, pos, val)
      if (pos >= node.right!.start) this.modifyNode(node.right!, pos, val)
      this.pushup(node)
    }
  }

  // 使用 modify 和 modifyRange 是等价的，modifyRange 更加通用
  modifyRange (start: number, end: number, val: number) {
    this.modifyNodeRange(this.root, start, end, val)
  }

  modifyNodeRange (node: Node, start: number, end: number, val: number) {
    if (start <= node.start && end >= node.end) {
      node.sum = val * (node.end - node.start + 1)
      node.max = val
      node.lazy = val
    } else {
      this.pushdown(node)
      if (start <= node.left!.end) this.modifyNodeRange(node.left!, start, end, val)
      if (end >= node.right!.start) this.modifyNodeRange(node.right!, start, end, val)
      this.pushup(node)
    }
  }

  // 这里 pushdown 同时保证了 left, right 一定存在
  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
    if (node.lazy != null) {
      node.left.lazy = node.lazy
      node.left.max = node.lazy
      node.left.sum = node.lazy * (node.left.end - node.left.start + 1)

      node.right.lazy = node.lazy
      node.right.max = node.lazy
      node.right.sum = node.lazy * (node.right.end - node.right.start + 1)

      node.lazy = null
    }
  }

  pushup (node: Node) {
    node.max = Math.max(node.left!.max, node.right!.max)
    node.sum = node.left!.sum + node.right!.sum
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) {
      return { max: node.max, sum: node.sum }
    }

    this.pushdown(node)
    let max = 0; let sum = 0
    if (start <= node.left!.end) {
      const { max: _m, sum: _s } = this.queryNode(node.left!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    if (end >= node.right!.start) {
      const { max: _m, sum: _s } = this.queryNode(node.right!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    return { max, sum }
  }
}
