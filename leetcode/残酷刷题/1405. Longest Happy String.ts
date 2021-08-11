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

function longestDiverseString (a: number, b: number, c: number): string {
  // [freq, char]
  const heap = new Heap<[number, string]>((a, b) => a[0] > b[0])
  if (a !== 0) heap.push([a, 'a'])
  if (b !== 0) heap.push([b, 'b'])
  if (c !== 0) heap.push([c, 'c'])

  let ans = ''
  while (heap.size()) {
    const x = heap.pop()
    if (heap.size() === 0) {
      for (let i = 0; i < Math.min(2, x[0]); i++) {
        ans += x[1]
      }
      continue
    }
    const y = heap.pop()
    let k = 1
    if (x[0] > y[0]) k = 2
    for (let i = 0; i < k; i++) ans += x[1]
    ans += y[1]

    x[0] -= k
    y[0] -= 1
    if (x[0]) heap.push(x)
    if (y[0]) heap.push(y)
  }
  return ans
};
