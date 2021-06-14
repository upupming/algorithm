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
有很多任务可以做的时候，选择 endDay 最早的来做
因此先将所有任务按照 startDay 排序，逐渐增大当前时间，将 startDay <= 当前时间的放入队列，将 endDay < 当前时间的出队，然后选择 endDay 最早的做即可
*/
function maxEvents (events: number[][]): number {
  const n = events.length
  events.sort((e1, e2) => e1[0] - e2[0])
  const heap = new Heap()
  let ans = 0
  for (let day = 1, i = 0; day <= 1e5; day++) {
    while (i < n && events[i][0] <= day) {
      heap.push(events[i][1])
      i++
    }
    while (heap.size() && heap.top() < day) heap.pop()
    if (heap.size()) {
      ans++
      heap.pop()
    }
  }
  return ans
};
