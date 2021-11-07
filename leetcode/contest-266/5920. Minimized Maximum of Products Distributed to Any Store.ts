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

// 难受，用 JS 就很难往优先队列这个方向去想，导致想了很多不对的解法
function minimizedMaximum (n: number, quantities: number[]): number {
  const m = quantities.length
  let rest = n - m
  const up = (a: number, b: number) => Math.floor((a + b - 1) / b)
  const h = new Heap(quantities.map(q => [q, 1]), (l, r) => up(l[0], l[1]) > up(r[0], r[1]))
  while (rest) {
    const [q, cnt] = h.pop()
    h.push([q, cnt + 1])
    rest--
  }
  const now = h.pop()
  return up(now[0], now[1])
};
