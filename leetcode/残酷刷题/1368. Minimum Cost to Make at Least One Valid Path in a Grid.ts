function minCost (grid: number[][]): number {
  const [m, n] = [grid.length, grid[0].length]
  type Pos = [number, number]
  const h = new Heap<[Pos, number]>([[[0, 0], 0]], (a, b) => a[1] < b[1])
  const dx = [-1, 0, 0, 1, -1]
  const dy = [-1, 1, -1, 0, 0]
  const valid = ([x, y]: Pos) => {
    return x >= 0 && x < m && y >= 0 && y < n
  }
  const v: Record<string, boolean> = {}
  while (h.size()) {
    const [pos, cost] = h.pop()
    if (pos[0] === m - 1 && pos[1] === n - 1) return cost
    const hash = `${pos[0]}_${pos[1]}`
    if (v[hash]) continue
    v[hash] = true
    for (let k = 1; k <= 4; k++) {
      const nextPos: Pos = [pos[0] + dx[k], pos[1] + dy[k]]
      if (!valid(nextPos)) continue
      const newCost = cost + (k === grid[pos[0]][pos[1]] ? 0 : 1)
      h.push([nextPos, newCost])
    }
  }
};

// This is just to make the file being treated as a module
// Cannot use export {} because LeetCode compiled to esmodule but can only run cjs
export declare const _: any

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
