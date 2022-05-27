/**
 * @param {number[][]} buildings
 * @return {number[][]}
 */
const getSkyline = function (b) {
  const a = []; const h = new RemovableHeap((a, b) => b - a)
  for (const [l, r, h] of b) {
    a.push([l, h, 1])
    a.push([r, h, -1])
  }
  a.sort((x, y) => x[0] - y[0])
  const ans = []
  for (let i = 0; i < a.length;) {
    const x = a[i][0]; let j = i
    while (j < a.length && a[j][0] === x) {
      const [_, y, f] = a[j]
      if (f === -1) h.remove(y)
      else h.push(y)
      j++
    }
    i = j
    const cur = h.top() ?? 0
    if (!ans.length || ans[ans.length - 1][1] !== cur) {
      ans.push([x, cur])
    }
  }
  return ans
}

class Heap {
  constructor (data = [], compare = (lhs, rhs) => lhs < rhs ? -1 : lhs > rhs ? 1 : 0) {
    if (typeof data === 'function') {
      compare = data
      data = []
    }
    this.data = [null, ...data]
    this.lt = (i, j) => compare(this.data[i], this.data[j]) < 0
    for (let i = this.size(); i > 0; i--) { this.heapify(i) }
  }

  size () {
    return this.data.length - 1
  }

  push (v) {
    this.data.push(v)
    let i = this.size()
    while (i >> 1 !== 0 && this.lt(i, i >> 1)) { this.swap(i, i >>= 1) }
  }

  pop () {
    this.swap(1, this.size())
    const top = this.data.pop()
    this.heapify(1)
    return top
  }

  top () {
    return this.data[1]
  }

  heapify (i) {
    while (true) {
      let min = i
      const [l, r, n] = [i * 2, i * 2 + 1, this.data.length]
      if (l < n && this.lt(l, min)) { min = l }
      if (r < n && this.lt(r, min)) { min = r }
      if (min !== i) {
        this.swap(i, min)
        i = min
      } else { break }
    }
  }

  clear () {
    this.data = [null]
  }

  swap (i, j) {
    const d = this.data;
    [d[i], d[j]] = [d[j], d[i]]
  }
}

class RemovableHeap {
  constructor (data = [], cmp) {
    this.heap = new Heap(data, cmp)
    this.counts = new Map()
    this._invalidCount = 0
    for (let i = 1; i < this.heap.data.length; i++) {
      this._setCount(this.heap.data[i], 1)
    }
  }

  size () {
    return this.heap.size() - this._invalidCount
  }

  top () {
    this._normalize()
    return this.heap.top()
  }

  pop () {
    this._normalize()
    if (this.heap.size() < 1) { return void 0 }
    const top = this.heap.pop()
    this._setCount(top, -1)
    return top
  }

  push (num) {
    this._setCount(num, 1)
    this.heap.push(num)
  }

  remove (num) {
    if (Number(this.counts.get(num)) > 0) {
      this._setCount(num, -1)
      this._invalidCount++
    }
  }

  has (value) {
    return this.counts.get(value) > 0
  }

  _setCount (num, diff) {
    let _a
    const count = (_a = this.counts.get(num)) != null ? _a : 0
    this.counts.set(num, count + diff)
  }

  _normalize () {
    while (this.heap.size() && !this.counts.get(this.heap.top())) {
      this.heap.pop()
      this._invalidCount--
    }
  }
}
