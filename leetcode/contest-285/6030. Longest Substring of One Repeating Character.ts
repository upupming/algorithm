function longestRepeating (s: string, queryCharacters: string, queryIndices: number[]): number[] {
  const t = s.split('')
  const n = s.length; const m = queryCharacters.length
  const ans: number[] = []
  // 存储所有区间长度
  const lens = new TreeMultiSet<number>()
  // 存储所有区间
  const st = Array(26).fill(0).map(() => new TreeMultiSet<string>([], (x, y) => {
    return x < y
  }))
  for (let i = 0; i < n; i++) ins(s.charCodeAt(i) - 'a'.charCodeAt(0), i)
  for (let i = 0; i < m; i++) {
    const qi = queryIndices[i]
    const qc = queryCharacters[i]
    if (t[qi] === qc) {
      ans.push(lens.rvalues().next().value!)
      continue
    }
    brk(t[qi].charCodeAt(0) - 'a'.charCodeAt(0), qi)
    ins(qc.charCodeAt(0) - 'a'.charCodeAt(0), qi)
    t[qi] = qc
    ans.push(lens.rvalues().next().value!)
  }
  return ans

  function construct (l: number, r: number) {
    return `${l.toString().padStart(6, '0')}_${r.toString().padStart(6, '0')}`
  }

  // 加入 c 的连续字符串 [L, R)
  function add (c: number, l: number, r: number) {
    lens.add(r - l)
    st[c].add(construct(l, r))
  }
  function del (c: number, l: number, r: number) {
    lens.delete(r - l)
    st[c].delete(construct(l, r))
  }
  function brk (c: number, idx: number) {
    const x = st[c].lower(construct(idx + 1, 0))!
    const [l, r] = x.split('_').map(Number)
    del(c, l, r)
    if (l < idx) add(c, l, idx)
    if (idx + 1 < r) add(c, idx + 1, r)
  }
  function ins (c: number, idx: number) {
    add(c, idx, idx + 1)
    const cur: [number, number] = [idx, idx + 1]
    // 尝试和左边的合并
    const x = st[c].lower(construct(cur[0], cur[1]))
    const l = x?.split('_').map(Number)
    if (l != null) {
      if (l[1] === cur[0]) {
        del(c, l[0], l[1])
        del(c, cur[0], cur[1])
        add(c, l[0], cur[1])
        cur[0] = l[0]
      }
    }
    // 尝试和右边的合并
    const y = st[c].ceiling(construct(cur[1], 0))
    const r = y?.split('_').map(Number)
    if (r != null) {
      if (r[0] === cur[1]) {
        del(c, cur[0], cur[1])
        del(c, r[0], r[1])
        add(c, cur[0], r[1])
      }
    }
  }
};
class RBTreeNode<T=number> {
  data: T
  left: RBTreeNode<T> | null
  right: RBTreeNode<T>| null
  parent: RBTreeNode<T>| null
  color: number
  constructor (data: T) {
    this.data = data
    this.left = this.right = this.parent = null
    this.color = 0
  }

  sibling (): RBTreeNode<T> | null {
    if (!this.parent) return null // sibling null if no parent
    return this.isOnLeft() ? this.parent.right : this.parent.left
  }

  isOnLeft (): boolean { return this === this.parent!.left }
  hasRedChild (): boolean {
    return Boolean(this.left && this.left.color === 0) || Boolean(this.right && this.right.color === 0)
  }
}

class RBTree<T> {
  root: RBTreeNode<T> | null
  compare: (l: T, r: T) => boolean
  constructor (compare = (l: T, r: T) => l < r) {
    this.root = null
    this.compare = compare
  }

  rotateLeft (pt: RBTreeNode<T>): void {
    const right = pt.right!
    pt.right = right.left

    if (pt.right) pt.right.parent = pt
    right.parent = pt.parent

    if (!pt.parent) this.root = right
    else if (pt === pt.parent.left) pt.parent.left = right
    else pt.parent.right = right

    right.left = pt
    pt.parent = right
  }

  rotateRight (pt: RBTreeNode<T>): void {
    const left = pt.left!
    pt.left = left.right

    if (pt.left) pt.left.parent = pt
    left.parent = pt.parent

    if (!pt.parent) this.root = left
    else if (pt === pt.parent.left) pt.parent.left = left
    else pt.parent.right = left

    left.right = pt
    pt.parent = left
  }

  swapColor (p1: RBTreeNode<T>, p2: RBTreeNode<T>): void {
    const tmp = p1.color
    p1.color = p2.color
    p2.color = tmp
  }

  swapData (p1: RBTreeNode<T>, p2: RBTreeNode<T>): void {
    const tmp = p1.data
    p1.data = p2.data
    p2.data = tmp
  }

  fixAfterInsert (pt: RBTreeNode<T>): void {
    let parent = null
    let grandParent = null

    while (pt !== this.root && pt.color !== 1 && pt.parent?.color === 0) {
      parent = pt.parent
      grandParent = pt.parent.parent

      /*  Case : A
                Parent of pt is left child of Grand-parent of pt */
      if (parent === grandParent?.left) {
        const uncle = grandParent.right

        /* Case : 1
                   The uncle of pt is also red
                   Only Recoloring required */
        if (uncle && uncle.color === 0) {
          grandParent.color = 0
          parent.color = 1
          uncle.color = 1
          pt = grandParent
        } else {
          /* Case : 2
                       pt is right child of its parent
                       Left-rotation required */
          if (pt === parent.right) {
            this.rotateLeft(parent)
            pt = parent
            parent = pt.parent
          }

          /* Case : 3
                       pt is left child of its parent
                       Right-rotation required */
          this.rotateRight(grandParent)
          this.swapColor(parent!, grandParent)
          pt = parent!
        }
      }

      /* Case : B
               Parent of pt is right child of Grand-parent of pt */
      else {
        const uncle = grandParent!.left

        /*  Case : 1
                    The uncle of pt is also red
                    Only Recoloring required */
        if ((uncle != null) && (uncle.color === 0)) {
          grandParent!.color = 0
          parent.color = 1
          uncle.color = 1
          pt = grandParent!
        } else {
          /* Case : 2
                       pt is left child of its parent
                       Right-rotation required */
          if (pt === parent.left) {
            this.rotateRight(parent)
            pt = parent
            parent = pt.parent
          }

          /* Case : 3
                       pt is right child of its parent
                       Left-rotation required */
          this.rotateLeft(grandParent!)
          this.swapColor(parent!, grandParent!)
          pt = parent!
        }
      }
    }
    this.root!.color = 1
  }

  deleteByValue (val: T): boolean {
    const node = this.search(val)
    if (node?.data !== val) return false
    this.deleteNode(node)
    return true
  }

  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  search (val: T): RBTreeNode<T> | null {
    let p = this.root
    while (p) {
      if (this.compare(val, p.data)) {
        if (!p.left) break
        else p = p.left
      } else if (this.compare(p.data, val)) {
        if (!p.right) break
        else p = p.right
      } else break
    }
    return p
  }

  deleteNode (v: RBTreeNode<T>): void {
    const u = BSTreplace(v)

    // True when u and v are both black
    const uvBlack = (u === null || u.color === 1) && v.color === 1
    const parent = v.parent!

    if (!u) {
      // u is null therefore v is leaf
      if (v === this.root) this.root = null // v is root, making root null
      else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          this.fixDoubleBlack(v)
        } else {
          // u or v is red
          if (v.sibling())
          // sibling is not null, make it red"
          { v.sibling()!.color = 0 }
        }
        // delete v from the tree
        if (v.isOnLeft()) parent.left = null
        else parent.right = null
      }
      return
    }

    if (!v.left || !v.right) {
      // v has 1 child
      if (v === this.root) {
        // v is root, assign the value of u to v, and delete u
        v.data = u.data
        v.left = v.right = null
      } else {
        // Detach v from tree and move u up
        if (v.isOnLeft()) parent.left = u
        else parent.right = u
        u.parent = parent
        if (uvBlack) this.fixDoubleBlack(u) // u and v both black, fix double black at u
        else u.color = 1 // u or v red, color u black
      }
      return
    }

    // v has 2 children, swap data with successor and recurse
    this.swapData(u, v)
    this.deleteNode(u)

    // find node that replaces a deleted node in BST
    function BSTreplace (x: RBTreeNode<T>): RBTreeNode<T> | null {
      // when node have 2 children
      if (x.left && x.right) return successor(x.right)
      // when leaf
      if (!x.left && !x.right) return null
      // when single child
      return x.left ?? x.right
    }
    // find node that do not have a left child
    // in the subtree of the given node
    function successor (x: RBTreeNode<T>): RBTreeNode<T> {
      let temp = x
      while (temp.left) temp = temp.left
      return temp
    }
  }

  fixDoubleBlack (x: RBTreeNode<T>): void {
    if (x === this.root) return // Reached root

    const sibling = x.sibling(); const parent = x.parent!
    if (!sibling) {
      // No sibiling, double black pushed up
      this.fixDoubleBlack(parent)
    } else {
      if (sibling.color === 0) {
        // Sibling red
        parent.color = 0
        sibling.color = 1
        if (sibling.isOnLeft()) this.rotateRight(parent) // left case
        else this.rotateLeft(parent) // right case
        this.fixDoubleBlack(x)
      } else {
        // Sibling black
        if (sibling.hasRedChild()) {
          // at least 1 red children
          if (sibling.left && sibling.left.color === 0) {
            if (sibling.isOnLeft()) {
              // left left
              sibling.left.color = sibling.color
              sibling.color = parent.color
              this.rotateRight(parent)
            } else {
              // right left
              sibling.left.color = parent.color
              this.rotateRight(sibling)
              this.rotateLeft(parent)
            }
          } else {
            if (sibling.isOnLeft()) {
              // left right
              sibling.right!.color = parent.color
              this.rotateLeft(sibling)
              this.rotateRight(parent)
            } else {
              // right right
              sibling.right!.color = sibling.color
              sibling.color = parent.color
              this.rotateLeft(parent)
            }
          }
          parent.color = 1
        } else {
          // 2 black children
          sibling.color = 0
          if (parent.color === 1) this.fixDoubleBlack(parent)
          else parent.color = 1
        }
      }
    }
  }

  insert (data: T): boolean {
    const node = new RBTreeNode(data)
    const parent = this.search(data)
    if (!parent) this.root = node
    else if (this.compare(node.data, parent.data)) parent.left = node
    else if (this.compare(parent.data, node.data)) parent.right = node
    else return false
    node.parent = parent
    this.fixAfterInsert(node)
    return true
  }

  find (data: T): RBTreeNode<T> | null {
    const node = this.search(data)
    return node && node.data === data ? node : null
  }

  * inOrder (root: RBTreeNode<T> = this.root!): Generator<T, void, void> {
    if (!root) return
    for (const v of this.inOrder(root.left!)) yield v
    yield root.data
    for (const v of this.inOrder(root.right!)) yield v
  }

  * reverseInOrder (root: RBTreeNode<T> = this.root!): Generator<T, void, void> {
    if (!root) return
    for (const v of this.reverseInOrder(root.right!)) yield v
    yield root.data
    for (const v of this.reverseInOrder(root.left!)) yield v
  }
}

class TreeMultiSet<T = number> {
  _size: number
  tree: RBTree<T>
  counts: Map<T, number>
  compare: (l: T, r: T) => boolean
  constructor (collection: T[] = [], compare = (l: T, r: T) => l < r) {
    this._size = 0
    this.tree = new RBTree(compare)
    this.counts = new Map()
    this.compare = compare
    for (const val of collection) this.add(val)
  }

  size (): number {
    return this._size
  }

  has (val: T): boolean {
    return !!this.tree.find(val)
  }

  add (val: T): void {
    this.tree.insert(val)
    this.increase(val)
    this._size++
  }

  delete (val: T): void {
    this.decrease(val)
    if (this.count(val) === 0) {
      this.tree.deleteByValue(val)
    }
    this._size--
  }

  count (val: T): number {
    return this.counts.get(val) ?? 0
  }

  ceiling (val: T): T | undefined {
    let p = this.tree.root
    let higher = null
    while (p) {
      if (!this.compare(p.data, val)) {
        higher = p
        p = p.left
      } else {
        p = p.right
      }
    }
    return higher?.data
  }

  floor (val: T): T | undefined {
    let p = this.tree.root
    let lower = null
    while (p) {
      if (!this.compare(val, p.data)) {
        lower = p
        p = p.right
      } else {
        p = p.left
      }
    }
    return lower?.data
  }

  higher (val: T): T | undefined {
    let p = this.tree.root
    let higher = null
    while (p) {
      if (this.compare(val, p.data)) {
        higher = p
        p = p.left
      } else {
        p = p.right
      }
    }
    return higher?.data
  }

  lower (val: T): T | undefined {
    let p = this.tree.root
    let lower = null
    while (p) {
      if (this.compare(p.data, val)) {
        lower = p
        p = p.right
      } else {
        p = p.left
      }
    }
    return lower?.data
  }

  * keys (): Generator<T, void, void> {
    for (const val of this.values()) yield val
  }

  * values (): Generator<T, undefined, void> {
    for (const val of this.tree.inOrder()) {
      let count = this.count(val)
      while (count--) yield val
    }
    return undefined
  }

  /**
   * Return a generator for reverse order traversing the multi-set
   */
  * rvalues (): Generator<T, undefined, void> {
    for (const val of this.tree.reverseInOrder()) {
      let count = this.count(val)
      while (count--) yield val
    }
    return undefined
  }

  /**
   * Should only be called by `delete` to keep the internal state correct
   */
  private decrease (val: T): void {
    this.counts.set(val, this.count(val) - 1)
  }
  /**
   * Should only be called by `add` to keep the internal state correct
   */

  private increase (val: T): void {
    this.counts.set(val, this.count(val) + 1)
  }
}

export declare let xxx: any
