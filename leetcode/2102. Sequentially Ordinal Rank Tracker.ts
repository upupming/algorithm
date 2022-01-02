type Item = [string, number]

const less = (x: Item, y: Item) => {
  // 数字相等的时候看字符串
  if (x[1] === y[1]) {
    return x[0] > y[0]
  } else {
    return x[1] < y[1]
  }
}
class SORTracker {
  i: number
  heapLeft: Heap<Item>
  heapRight: Heap<Item>
  constructor () {
    // 永远保持 heapLeft 的个数为 i
    this.heapLeft = new Heap(less)
    this.heapRight = new Heap((a, b) => !less(a, b))
    this.i = 1
  }

  add (name: string, score: number): void {
    this.heapLeft.push([name, score])
    while (this.heapLeft.size() > this.i) {
      const x = this.heapLeft.pop()!
      this.heapRight.push(x)
    }
  }

  get (): string {
    // 如果发现右边的更大，需要移过来
    while (this.heapRight.size() && less(this.heapLeft.top(), this.heapRight.top())) {
      const [x, y] = [this.heapLeft.pop(), this.heapRight.pop()]
      this.heapLeft.push(y)
      this.heapRight.push(x)
    }

    // console.log(this.i, this.heapLeft.data, this.heapRight.data)

    this.i++
    while (this.heapLeft.size() < this.i) {
      this.heapLeft.push(this.heapRight.pop())
    }

    return this.heapLeft.top()[0]
  }
}

/**
* Your SORTracker object will be instantiated and called as such:
* var obj = new SORTracker()
* obj.add(name,score)
* var param_2 = obj.get()
*/

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
