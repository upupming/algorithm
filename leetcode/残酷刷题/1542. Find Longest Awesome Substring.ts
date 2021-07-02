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
等价于求最长的串满足，这个串里面最多有一个数出现奇数次
状态 f 的每一位表示每个数出现的奇偶性
f[i] ^ f[j] 最多有 1 个 1，求最长的 [i, j] 区间

将 f[i] 反过来映射到下标 i，并且用最小堆存储即可，每次都可以拿到最小值
*/
function longestAwesome (s: string): number {
  const h = new Map<number, Heap>()
  let [f, ans] = [0, 0]
  h.set(0, new Heap([-1]))
  for (let i = 0; i < s.length; i++) {
    f ^= 1 << (s.charCodeAt(i) - '0'.charCodeAt(0))
    // 查找最小的满足条件的 j
    if (h.get(f)) {
      ans = Math.max(ans, i - h.get(f)!.top())
    }
    for (let k = 0; k < 10; k++) {
      const g = f ^ (1 << k)
      if (h.get(g)) {
        ans = Math.max(ans, i - h.get(g)!.top())
      }
    }
    // 将 i 放入 map 中
    if (h.get(f)) {
      h.get(f)?.push(i)
    } else {
      h.set(f, new Heap([i]))
    }
  }
  return ans
};
