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
用一个堆存储当前等待的 task，堆顶是需要处理时间最短的任务
*/
function getOrder (tasks: number[][]): number[] {
  const n = tasks.length
  for (let i = 0; i < n; i++) {
    tasks[i].push(i)
  }
  tasks.sort((t1, t2) => t1[0] - t2[0])
  const heap = new Heap((i, j) => {
    if (tasks[i][1] !== tasks[j][1]) {
      return tasks[i][1] < tasks[j][1]
    }
    return tasks[i][2] < tasks[j][2]
  })
  const ans = []
  let nextFreeTime = 0
  for (let i = 0; i < n;) {
    const curTime = tasks[i][0]
    // 处理完前面的任务
    while (heap.size() && nextFreeTime < curTime) {
      const t = heap.pop()
      nextFreeTime += tasks[t][1]
      ans.push(tasks[t][2])
    }
    // CPU 空闲等待，直到当前时间
    nextFreeTime = Math.max(nextFreeTime, curTime)
    let j = i
    while (j < n && tasks[j][0] === curTime) {
      heap.push(j++)
    }
    i = j
  }
  // 剩余任务顺序处理
  while (heap.size()) {
    ans.push(tasks[heap.pop()][2])
  }
  return ans
};
