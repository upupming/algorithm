class BookMyShow {
  // 每一行剩余的座椅数目
  seats: number[]
  // 当前仍有座位剩余的最小行号
  p: number
  tree: SegmentTree
  m: number
  constructor (n: number, m: number) {
    this.m = m
    this.seats = Array(n).fill(m)
    this.p = 0
    this.tree = new SegmentTree(0, n)
    // 初始情况，每个节点都有 m 个座位
    for (let i = 0; i < n; i++) {
      this.tree.modify(i, m)
    }
  }

  gather (k: number, maxRow: number): number[] {
    let l = 0; let r = maxRow
    while (l < r) {
      const mid = l + r >> 1
      const [max, sum] = this.tree.query(0, mid)
      if (max >= k) r = mid
      else l = mid + 1
    }
    const [max, sum] = this.tree.query(0, l)
    if (max < k) return []
    this.seats[l] -= k
    // 使用 modify 和 modifyRange 是等价的，modifyRange 更加通用
    // this.tree.modify(l, this.seats[l])
    this.tree.modifyRange(l, l, this.seats[l])
    return [l, this.m - this.seats[l] - k]
  }

  scatter (k: number, maxRow: number): boolean {
    const [max, sum] = this.tree.query(0, maxRow)
    if (sum < k) return false
    while (k) {
      const t = Math.min(this.seats[this.p], k)
      k -= t
      this.seats[this.p] -= t
      // this.tree.modify(this.p, this.seats[this.p])
      this.tree.modifyRange(this.p, this.p, this.seats[this.p])
      if (this.seats[this.p] === 0) this.p++
    }
    return true
  }
}

/**
* Your BookMyShow object will be instantiated and called as such:
* var obj = new BookMyShow(n, m)
* var param_1 = obj.gather(k,maxRow)
* var param_2 = obj.scatter(k,maxRow)
*/

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
      node.sum = val * (end - start + 1)
      node.max = val
      node.lazy = val
    } else {
      this.pushdown(node)
      if (start <= node.left!.end) this.modifyNodeRange(node.left!, start, end, val)
      if (end >= node.right!.start) this.modifyNodeRange(node.right!, start, end, val)
      this.pushup(node)
    }
  }

  // 这里 pushdown 的作用只是动态创建新节点
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
    if (start <= node.start && end >= node.end) return [node.max, node.sum]

    this.pushdown(node)
    let max = 0; let sum = 0
    if (start <= node.left!.end) {
      const [_m, _s] = this.queryNode(node.left!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    if (end >= node.right!.start) {
      const [_m, _s] = this.queryNode(node.right!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    return [max, sum]
  }
}
