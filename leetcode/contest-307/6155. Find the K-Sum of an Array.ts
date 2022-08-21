// https://leetcode.cn/circle/discuss/t6hE2C/view/MwcHdY/
function kSum (nums: number[], k: number): number {
  const a = nums.map(BigInt)
  const n = a.length
  let sum = 0n; let negSum = 0n
  for (let i = 0; i < n; i++) {
    sum += a[i]
    if (a[i] < 0n) {
      negSum += a[i]
      a[i] = -a[i]
    }
  }
  a.sort((a, b) => a < b ? -1 : 1)

  const heap = new Heap<[bigint, number]>((a, b) => a[0] < b[0] ? -1 : 1)
  let ans = 0n
  heap.push([a[0], 0])
  for (let l = 2; l <= k; l++) {
    ans = ans < heap.top()[0] ? heap.top()[0] : ans
    const [s, i] = heap.pop()
    if (i === n - 1) continue
    heap.push([s + a[i + 1], i + 1])
    heap.push([s - a[i] + a[i + 1], i + 1])
  }
  return Number(sum - (ans + negSum))
};

export declare const a: 1

/**
 * 默认是小根堆，修改排序函数可以改成大根堆
 */
class Heap<T = number> {
  _data: T[] = [null as unknown as T]
  compareFn: (a: T, b: T) => number
  constructor (compareFn: (a: T, b: T) => number = (a: T, b: T) => a < b ? -1 : (a > b ? 1 : 0)) {
    this.compareFn = compareFn
  }

  _swap (i: number, j: number) {
    [this._data[i], this._data[j]] = [this._data[j], this._data[i]]
  }

  _up (p: number) {
    while (p > 1) {
      // 如果 p 应该在父亲节点前面，就交换位置
      if (this.compareFn(this._data[p], this._data[p >> 1]) < 0) {
        this._swap(p, p >> 1)
        p >>= 1
      } else break
    }
  }

  _down (p: number) {
    let s = p << 1
    while (s < this._data.length) {
      if (s + 1 < this._data.length && this.compareFn(this._data[s + 1], this._data[s]) < 0) s++
      if (this.compareFn(this._data[s], this._data[p]) < 0) {
        this._swap(s, p)
        p = s, s = p << 1
      } else break
    }
  }

  push (val: T) {
    this._data.push(val)
    this._up(this._data.length - 1)
  }

  top () {
    return this._data[1]
  }

  pop () {
    const val = this._data[1]
    this._data[1] = this._data[this._data.length - 1]
    this._data.pop()
    this._down(1)
    return val
  }

  /** 删除第 k 个元素 */
  remove (k: number) {
    this._data[k] = this._data[this._data.length - 1]
    this._data.pop()
    this._up(k)
    this._down(k)
  }

  get size () {
    return this._data.length - 1
  }
}
