/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} succProb
 * @param {number} start
 * @param {number} end
 * @return {number}
 */
const maxProbability = function (n, edges, succProb, start, end) {
  const h = new Heap([[start, 1]], (a, b) => a[1] > b[1])
  const e = Array(n).fill(0).map(() => [])
  for (let i = 0; i < edges.length; i++) {
    e[edges[i][0]].push([edges[i][1], succProb[i]])
    e[edges[i][1]].push([edges[i][0], succProb[i]])
  }
  const d = Array(n).fill(0)
  while (h.size()) {
    const [x, p] = h.pop()
    if (d[x] > 0) continue
    d[x] = p
    for (const [y, c] of e[x]) {
      if (d[y] < p * c) {
        h.push([y, p * c])
      }
    }
  }
  return d[end]
}

class Heap {
  constructor (data = [], cmp = (lhs, rhs) => lhs < rhs) {
    if (typeof data === 'function') {
      cmp = data
      data = []
    }
    this.data = [null, ...data]
    this.lt = (i, j) => cmp(this.data[i], this.data[j])
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

  swap (i, j) {
    const d = this.data;
    [d[i], d[j]] = [d[j], d[i]]
  }
}
