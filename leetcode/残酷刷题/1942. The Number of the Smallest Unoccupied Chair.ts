export {}
class Heap<T=number> {
  data: Array<T | null>
  lt: (i: number, j: number) => boolean
  constructor ()
  constructor (data: T[])
  constructor (cmp: (lhs: T, rhs: T) => boolean)
  constructor (data: T[], cmp: (lhs: T, rhs: T) => boolean)
  constructor (data: (T[] | ((lhs: T, rhs: T) => boolean)), cmp: (lhs: T, rhs: T) => boolean)
  constructor (data: (T[] | ((lhs: T, rhs: T) => boolean)) = [], cmp = (lhs: T, rhs: T) => lhs < rhs) {
    if (typeof data === 'function') {
      cmp = data
      data = []
    }
    this.data = [null, ...data]
    this.lt = (i, j) => cmp(this.data[i]!, this.data[j]!)
    for (let i = this.size(); i > 0; i--) this.heapify(i)
  }

  size (): number {
    return this.data.length - 1
  }

  push (v: T): void {
    this.data.push(v)
    let i = this.size()
    while ((i >> 1 !== 0) && this.lt(i, i >> 1)) this.swap(i, i >>= 1)
  }

  pop (): T {
    this.swap(1, this.size())
    const top = this.data.pop()
    this.heapify(1)
    return top!
  }

  top (): T { return this.data[1]! }
  heapify (i: number): void {
    while (true) {
      let min = i
      const [l, r, n] = [i * 2, i * 2 + 1, this.data.length]
      if (l < n && this.lt(l, min)) min = l
      if (r < n && this.lt(r, min)) min = r
      if (min !== i) {
        this.swap(i, min); i = min
      } else break
    }
  }

  swap (i: number, j: number): void {
    const d = this.data;
    [d[i], d[j]] = [d[j], d[i]]
  }
}

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
}

class TreeSet<T = number> {
  #size: number
  tree: RBTree<T>
  compare: (l: T, r: T) => boolean
  constructor (collection: T[] = [], compare = (l: T, r: T) => l < r) {
    this.#size = 0
    this.tree = new RBTree(compare)
    this.compare = compare
    for (const val of collection) this.add(val)
  }

  size (): number {
    return this.#size
  }

  has (val: T): boolean {
    return !!this.tree.find(val)
  }

  add (val: T): boolean {
    const added = this.tree.insert(val)
    this.#size += added ? 1 : 0
    return added
  }

  delete (val: T): boolean {
    const deleted = this.tree.deleteByValue(val)
    this.#size -= deleted ? 1 : 0
    return deleted
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

  * [Symbol.iterator] (): Generator<T, void, void> {
    for (const val of this.values()) yield val
  }

  * keys (): Generator<T, void, void> {
    for (const val of this.values()) yield val
  }

  * values (): Generator<T, void, void> {
    for (const val of this.tree.inOrder()) yield val
  }
}

function smallestChair (times: number[][], targetFriend: number): number {
  const n = times.length
  times.forEach((t, i) => t.push(i))
  times.sort((a, b) => a[0] - b[0])
  const seats = new TreeSet([...Array(n)].map((_, i) => i))
  const heap = new Heap<{
    leave: number
    seat: number
  }>((a, b) => a.leave < b.leave)
  for (const time of times) {
    const [arrival, leaving] = time
    while (heap.size() && heap.top().leave <= arrival) {
      const { seat } = heap.pop()
      seats.add(seat)
    }
    const s = seats.values().next().value as number
    seats.delete(s)
    heap.push({ leave: leaving, seat: s })
    if (time[2] === targetFriend) return s
  }
  return -1
};
