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

/**
 * 先按照 wage/quality 排序，不断增加最高 wage/quality 比，在 PQ 中不断加入员工，加入之后选择最省钱的 k 个员工即可（也就是 quality 最小的就行了），弹出最大员工即可
 * @param {number[]} quality
 * @param {number[]} wage
 * @param {number} k
 * @return {number}
 */
const mincostToHireWorkers = function (quality, wage, k) {
  const n = quality.length
  const idx = Array(n).fill(0).map((_, idx) => idx)
  idx.sort((i, j) => wage[i] / quality[i] - wage[j] / quality[j])
  let qualitySum = 0; let ans = 1e10
  // max heap
  const heap = new Heap([], (i, j) => quality[i] > quality[j])
  for (const i of idx) {
    qualitySum += quality[i]
    heap.push(i)
    const ratio = wage[i] / quality[i]
    while (heap.size() > k) {
      qualitySum -= quality[heap.pop()]
    }
    if (heap.size() === k) {
      ans = Math.min(ans, qualitySum * ratio)
    }
  }
  return ans
}
