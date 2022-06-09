function longestRepeating (s: string, queryCharacters: string, queryIndices: number[]): number[] {
  const tree = new SegmentTree(0, s.length)
  for (let i = 0; i < s.length; i++) {
    tree.modify(i, s[i])
  }
  const ans = []
  for (let i = 0; i < queryCharacters.length; i++) {
    tree.modify(queryIndices[i], queryCharacters[i])
    ans.push(Math.max(...tree.query(0, s.length)))
  }
  return ans
};

export declare const a: 1

class Node {
  start: number
  end: number
  maxLen: number[]
  leftMaxLen: number[]
  rightMaxLen: number[]
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
    this.maxLen = Array(26).fill(0)
    this.leftMaxLen = Array(26).fill(0)
    this.rightMaxLen = Array(26).fill(0)
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (pos: number, char: string) {
    this.modifyNode(this.root, pos, char)
  }

  modifyNode (node: Node, pos: number, char: string) {
    if (node.start === pos && node.end === pos) {
      for (let i = 0; i < 26; i++) {
        node.leftMaxLen[i] = node.rightMaxLen[i] = node.maxLen[i] = char === (String.fromCharCode('a'.charCodeAt(0) + i)) ? 1 : 0
      }
    } else {
      this.pushdown(node)
      if (pos <= node.left!.end) this.modifyNode(node.left!, pos, char)
      if (pos >= node.right!.start) this.modifyNode(node.right!, pos, char)
      this.pushup(node)
    }
  }

  // 这里 pushdown 的作用只是动态创建新节点
  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
  }

  pushup (node: Node) {
    for (let i = 0; i < 26; i++) {
      node.leftMaxLen[i] = node.left!.leftMaxLen[i]
      if (node.left!.leftMaxLen[i] === node.left!.end - node.left!.start + 1) {
        node.leftMaxLen[i] = node.left!.leftMaxLen[i] + node.right!.leftMaxLen[i]
      }

      node.rightMaxLen[i] = node.right!.rightMaxLen[i]
      if (node.right!.rightMaxLen[i] === node.right!.end - node.right!.start + 1) {
        node.rightMaxLen[i] = node.right!.rightMaxLen[i] + node.left!.rightMaxLen[i]
      }

      node.maxLen[i] = Math.max(node.left!.maxLen[i], node.right!.maxLen[i], node.left!.rightMaxLen[i] + node.right!.leftMaxLen[i])
    }
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  arrayAdd (a: number[], b: number[]) {
    for (let i = 0; i < a.length; i++) a[i] += b[i]
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return node.maxLen

    this.pushdown(node)
    const sum = Array(26)
    if (start <= node.left!.end) this.arrayAdd(sum, this.queryNode(node.left!, start, end))
    if (end >= node.right!.start) this.arrayAdd(sum, this.queryNode(node.right!, start, end))
    return sum
  }
}
