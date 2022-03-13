function minimumWeight (n: number, edges: number[][], src1: number, src2: number, dest: number): number {
  type AdjList = Array<Array<[number, number]>>
  const adjList: AdjList = Array(n).fill(0).map(() => [])
  const reversedAdjList: AdjList = Array(n).fill(0).map(() => [])
  for (const [x, y, w] of edges) {
    adjList[x].push([y, w])
    reversedAdjList[y].push([x, w])
  }

  const d1 = dijkstra(adjList, src1)
  const d2 = dijkstra(adjList, src2)
  const d3 = dijkstra(reversedAdjList, dest)

  let ans = 1e12
  for (let i = 0; i < n; i++) {
    ans = Math.min(ans, d1[i] + d2[i] + d3[i])
  }
  if (ans === 1e12) ans = -1
  return ans

  function dijkstra (adjList: AdjList, source: number) {
    const h = new Heap<[number, number]>([], (a, b) => a[1] < b[1])
    const d = Array<number>(n).fill(1e12)
    d[source] = 0
    h.push([source, 0])
    while (h.size()) {
      const [x, dx] = h.pop()
      if (dx > d[x]) continue
      for (const [y, w] of adjList[x]) {
        if (d[y] > d[x] + w) {
          d[y] = d[x] + w
          h.push([y, d[y]])
        }
      }
    }
    return d
  }
};

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

export {}
