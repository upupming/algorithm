class RangeModule {
  tree: SegmentTree
  constructor () {
    this.tree = new SegmentTree(0, 1e9)
  }

  addRange (left: number, right: number): void {
    this.tree.modify(left, right - 1, true)
  }

  queryRange (left: number, right: number): boolean {
    return this.tree.query(left, right - 1) === right - left
  }

  removeRange (left: number, right: number): void {
    this.tree.modify(left, right - 1, false)
  }
}

export declare const a: 1

enum Tracked {
  TRUE = 'TRUE',
  FALSE = 'FALSE'
}

class Node {
  start: number
  end: number
  val: number = 0
  lazy: Tracked | null = null
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

  modify (start: number, end: number, tracked: boolean) {
    this.modifyNode(this.root, start, end, tracked)
  }

  modifyNode (node: Node, start: number, end: number, tracked: boolean) {
    if (start <= node.start && end >= node.end) {
      node.val = tracked ? (node.end - node.start + 1) : 0
      node.lazy = tracked ? Tracked.TRUE : Tracked.FALSE
    } else {
      this.pushdown(node)
      // pushdown 已经确保 left 和 right 一定存在了
      if (start <= node.left!.end) this.modifyNode(node.left!, start, end, tracked)
      if (end >= node.right!.start) this.modifyNode(node.right!, start, end, tracked)
      this.pushup(node)
    }
  }

  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
    if (node.lazy) {
      node.left.lazy = node.lazy
      node.left.val = (node.lazy === Tracked.TRUE) ? (node.left.end - node.left.start + 1) : 0

      node.right.lazy = node.lazy
      node.right.val = (node.lazy === Tracked.TRUE) ? (node.right.end - node.right.start + 1) : 0

      node.lazy = null
    }
  }

  pushup (node: Node) {
    node.val = node.left!.val + node.right!.val
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return node.val

    this.pushdown(node)
    let sum = 0
    if (start <= node.left!.end) sum += this.queryNode(node.left!, start, end)
    if (end >= node.right!.start) sum += this.queryNode(node.right!, start, end)
    return sum
  }
}
