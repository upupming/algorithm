/**
 * @param {number[][]} grid
 * @return {number}
 */
const minimumObstacles = function (g) {
  const m = g.length; const n = g[0].length
  const dx = [0, 0, 1, -1]; const dy = [1, -1, 0, 0]
  const valid = (x, y) => x >= 0 && x < m && y >= 0 && y < n

  const q = new Deque([[0, 0, 0]]); const v = {}
  while (q.size()) {
    const [i, j, cd] = q.shift()
    if (v[`${i}_${j}`]) continue
    v[`${i}_${j}`] = 1
    if (i === m - 1 && j === n - 1) return cd
    for (let k = 0; k < 4; k++) {
      const x = i + dx[k]; const y = j + dy[k]
      if (valid(x, y) && !v[`${x}_${y}`]) {
        if (g[x][y] === 0) q.unshift([x, y, cd])
        else q.push([x, y, cd + 1])
      }
    }
  }
}

class CircularDeque {
  constructor (N) {
    this.prev = this.next = null
    this.begin = this.end = 0
    this.empty = true
    this.data = Array(N)
  }

  isFull () {
    return this.end === this.begin && !this.empty
  }

  isEmpty () {
    return this.empty
  }

  push (val) {
    if (this.isFull()) { return false }
    this.empty = false
    this.data[this.end] = val
    this.end = (this.end + 1) % this.data.length
    return true
  }

  front () {
    return this.isEmpty() ? void 0 : this.data[this.begin]
  }

  back () {
    return this.isEmpty() ? void 0 : this.data[this.end - 1]
  }

  pop () {
    if (this.isEmpty()) { return void 0 }
    const value = this.data[this.end - 1]
    this.end = (this.end - 1) % this.data.length
    if (this.end < 0) { this.end += this.data.length }
    if (this.end === this.begin) { this.empty = true }
    return value
  }

  unshift (val) {
    if (this.isFull()) { return false }
    this.empty = false
    this.begin = (this.begin - 1) % this.data.length
    if (this.begin < 0) { this.begin += this.data.length }
    this.data[this.begin] = val
    return true
  }

  shift () {
    if (this.isEmpty()) { return void 0 }
    const value = this.data[this.begin]
    this.begin = (this.begin + 1) % this.data.length
    if (this.end === this.begin) { this.empty = true }
    return value
  }

  * values () {
    if (this.isEmpty()) { return void 0 }
    let i = this.begin
    do {
      yield this.data[i]
      i = (i + 1) % this.data.length
    } while (i !== this.end)
  }
}
class Deque {
  constructor (collection = []) {
    this.head = new CircularDeque(128)
    this.tail = new CircularDeque(128)
    this.tail.empty = this.head.empty = false
    this.tail.prev = this.head
    this.head.next = this.tail
    this._size = 0
    for (const item of collection) { this.push(item) }
  }

  size () {
    return this._size
  }

  push (val) {
    let last = this.tail.prev
    if (last.isFull()) {
      const inserted = new CircularDeque(128)
      this.tail.prev = inserted
      inserted.next = this.tail
      last.next = inserted
      inserted.prev = last
      last = inserted
    }
    last.push(val)
    this._size++
  }

  back () {
    if (this._size === 0) { return }
    return this.tail.prev.back()
  }

  pop () {
    if (this.head.next === this.tail) { return void 0 }
    const last = this.tail.prev
    const value = last.pop()
    if (last.isEmpty()) {
      this.tail.prev = last.prev
      last.prev.next = this.tail
    }
    this._size--
    return value
  }

  unshift (val) {
    let first = this.head.next
    if (first.isFull()) {
      const inserted = new CircularDeque(128)
      this.head.next = inserted
      inserted.prev = this.head
      inserted.next = first
      first.prev = inserted
      first = inserted
    }
    first.unshift(val)
    this._size++
  }

  shift () {
    if (this.head.next === this.tail) { return void 0 }
    const first = this.head.next
    const value = first.shift()
    if (first.isEmpty()) {
      this.head.next = first.next
      first.next.prev = this.head
    }
    this._size--
    return value
  }

  front () {
    if (this._size === 0) { return void 0 }
    return this.head.next.front()
  }

  * values () {
    let node = this.head.next
    while (node !== this.tail) {
      for (const value of node.values()) { yield value }
      node = node.next
    }
  }
}
