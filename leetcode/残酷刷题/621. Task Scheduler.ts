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

function leastInterval (tasks: string[], n: number): number {
  n++
  const heap = new Heap((a, b) => a > b)
  const cnt = Array(26).fill(0)
  for (const t of tasks) {
    cnt[t.charCodeAt(0) - 'A'.charCodeAt(0)]++
  }
  for (let i = 0; i < 26; i++) {
    if (cnt[i] > 0) heap.push(cnt[i])
  }
  let ans = 0
  while (heap.size()) {
    const m = Math.min(heap.size(), n)
    // console.log(m, ans)
    const tmp = []
    for (let i = 0; i < m; i++) {
      tmp.push(heap.pop() - 1)
      ans++
    }
    for (const t of tmp) {
      if (t > 0) {
        heap.push(t)
      }
    }
    // idle: 最后一轮没有必要加 idle
    if (heap.size() !== 0) {
      ans += n - m
    }
  }
  return ans
};
