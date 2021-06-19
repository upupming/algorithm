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
/*
speed 越大越好，但是要控制住 efficiency 的最小值不能太小
effi 从大到小遍历，依次放入能够放的所有 engineer，然后选其中最大的 k 个，因此只需要维护一个大小为 k 的最小堆即可
*/
function maxPerformance (n: number, s: number[], e: number[], k: number): number {
  const idx = [...Array(n)].map((_, idx) => idx)
  const heap = new Heap<bigint>()
  idx.sort((i, j) => e[j] - e[i])
  let [sum, ans] = [0n, 0n]
  for (let i = 0; i < n; i++) {
    const sb = BigInt(s[idx[i]])
    heap.push(sb)
    sum += sb
    while (heap.size() > k) {
      sum -= heap.pop()
    }
    if (ans < sum * BigInt(e[idx[i]])) {
      ans = sum * BigInt(e[idx[i]])
    }
  }
  const P = BigInt(1e9 + 7)
  return Number(ans % P)
};
