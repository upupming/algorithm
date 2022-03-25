/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
const findCheapestPrice = function (n, flights, src, dst, k) {
  const h = new Heap([[src, 0, 0]], (a, b) => a[1] < b[1])
  const d = Array(n).fill(0).map(() => Array(k + 2).fill(1e10))
  const e = Array(n).fill(0).map(() => [])
  for (const [u, v, w] of flights) {
    e[u].push([v, w])
  }
  while (h.size()) {
    const [x, w, c] = h.pop()
    if (c > k + 1) continue
    if (d[x][c] <= w) continue
    d[x][c] = w
    if (x === dst) return w
    for (const [y, yw] of e[x]) {
      if (w + yw < d[y][c + 1]) {
        h.push([y, w + yw, c + 1])
      }
    }
  }
  return -1
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
