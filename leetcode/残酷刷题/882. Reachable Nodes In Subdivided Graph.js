/**
 * @param {number[][]} edges
 * @param {number} maxMoves
 * @param {number} n
 * @return {number}
 */
const reachableNodes = function (edges, maxMoves, n) {
  const e = Array(n).fill(0).map(() => [])
  for (const [u, v, w] of edges) {
    e[u].push([v, w + 1])
    e[v].push([u, w + 1])
  }
  let ans = 0
  const dijkstra = () => {
    const d = Array(n).fill(1e10)
    const h = new Heap([[0, 0]], (a, b) => a[1] < b[1])
    while (h.size()) {
      const [x, w] = h.pop()
      if (d[x] !== 1e10) continue
      d[x] = w
      if (d[x] <= maxMoves)ans++
      for (const [y, c] of e[x]) {
        if (d[y] > w + c) {
          h.push([y, w + c])
        }
      }
    }
    return d
  }
  const d = dijkstra()
  for (const [u, v, w] of edges) {
    const cnt = Math.max(maxMoves - d[u], 0) + Math.max(maxMoves - d[v], 0)
    ans += Math.min(cnt, w)
  }
  return ans
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
