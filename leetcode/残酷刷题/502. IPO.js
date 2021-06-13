class Heap {
  constructor (data = [], cmp = (lhs, rhs) => lhs < rhs) {
    if (typeof data === 'function') {
      cmp = data
      data = []
    }
    this.data = [null, ...data]
    this.lt = (i, j) => cmp(this.data[i], this.data[j])
    for (let i = this.size(); i > 0; i--) this.heapify(i)
  }

  size () {
    return this.data.length - 1
  }

  push (v) {
    this.data.push(v)
    let i = this.size()
    while (i >> 1 && this.lt(i, i >> 1)) this.swap(i, i >>= 1)
  }

  pop () {
    this.swap(1, this.size())
    const top = this.data.pop()
    this.heapify(1)
    return top
  }

  top () { return this.data[1] }
  heapify (i) {
    while (true) {
      let min = i
      const [l, r, n] = [i * 2, i * 2 + 1, this.data.length]
      if (l < n && this.lt(l, min)) min = l
      if (r < n && this.lt(r, min)) min = r
      if (min !== i) this.swap(i, min), i = min
      else break
    }
  }

  swap (i, j) {
    const d = this.data;
    [d[i], d[j]] = [d[j], d[i]]
  }
}

class RemovableHeap {
  constructor (...args) {
    this.heap = new Heap(...args)
    this.counts = new Map()
    this._invalidCount = 0
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
    if (this.heap.size() < 1) return
    const top = this.heap.pop()
    this._count(top, -1)
    return top
  }

  push (num) {
    this._count(num, 1)
    this.heap.push(num)
  }

  remove (num) {
    if (this.counts.get(num) > 0) {
      this._count(num, -1)
      this._invalidCount++
    }
  }

  _count (num, diff) {
    const count = this.counts.get(num) || 0
    this.counts.set(num, count + diff)
  }

  _normalize () {
    while (this.heap.size() && !this.counts.get(this.heap.top())) {
      this.heap.pop()
      this._invalidCount--
    }
  }
}

/*
按照 capital 排序，每次 capital 更新，就把 profits 加入到候选优先队列中
优先队列堆顶是最大的 profits
*/
/**
 * @param {number} k
 * @param {number} w
 * @param {number[]} profits
 * @param {number[]} capital
 * @return {number}
 */
const findMaximizedCapital = function (k, w, profits, capital) {
  const n = profits.length
  const heap = new Heap([], (a, b) => a > b)
  const idx = Array(n).fill(0).map((val, idx) => idx)
  idx.sort((i, j) => capital[i] - capital[j])
  let i = 0
  while (i < n && capital[idx[i]] <= w) {
    heap.push(profits[idx[i]])
    i++
  }
  while (heap.size() && k--) {
    w += heap.top()
    heap.pop()
    while (i < n && capital[idx[i]] <= w) {
      heap.push(profits[idx[i]])
      i++
    }
  }
  return w
}
