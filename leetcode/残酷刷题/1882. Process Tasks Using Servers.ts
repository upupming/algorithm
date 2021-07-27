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

function assignTasks (servers: number[], tasks: number[]): number[] {
  const ans = []
  const free = new Heap<{
    weight: number
    index: number
  }>((a, b) => {
    if (a.weight !== b.weight) return a.weight < b.weight
    return a.index < b.index
  })
  const busy = new Heap<{
    endTime: number
    weight: number
    index: number
  }>((a, b) => {
    if (a.endTime !== b.endTime) return a.endTime < b.endTime
    if (a.weight !== b.weight) return a.weight < b.weight
    return a.index < b.index
  })

  for (let i = 0; i < servers.length; i++) {
    free.push({ weight: servers[i], index: i })
  };
  const jobs = []
  for (let i = 0; i < tasks.length; i++) {
    while (busy.size() && busy.top().endTime <= i) {
      const { weight, index } = busy.pop()
      free.push({
        weight,
        index
      })
    }
    jobs.push(i)
    while (free.size() && jobs.length) {
      const job = jobs.shift()!
      const { weight, index } = free.pop()
      busy.push({
        endTime: i + tasks[job],
        weight,
        index
      })
      ans[job] = index
    }
  }
  while (jobs.length) {
    const job = jobs.shift()!
    const { endTime, weight, index } = busy.pop()
    ans[job] = index
    busy.push({ endTime: endTime + tasks[job], weight, index })
  }
  return ans
}
