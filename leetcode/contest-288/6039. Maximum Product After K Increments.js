/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
const maximumProduct = function (nums, k) {
  const h = new Heap(nums.map(BigInt), (a, b) => a < b)
  while (k--) {
    const x = h.pop()
    h.push(x + 1n)
  }
  let ans = 1n
  while (h.size()) {
    ans = (ans * h.pop()) % BigInt(1e9 + 7)
  }
  return Number(ans)
}

class Heap {
  constructor (data = [], cmp = (lhs, rhs) => lhs < rhs) {
    if (typeof data === 'function') {
      cmp = data
      data = []
    }
    this.data = [null, ...data]
    this.lt = (i, j) => cmp(this.data[i], this.data[j])
    for (let i = this.size(); i > 0; i--) { this.heapify(i) }
  }

  size () {
    return this.data.length - 1
  }

  push (v) {
    this.data.push(v)
    let i = this.size()
    while (i >> 1 !== 0 && this.lt(i, i >> 1)) { this.swap(i, i >>= 1) }
  }

  pop () {
    this.swap(1, this.size())
    const top = this.data.pop()
    this.heapify(1)
    return top
  }

  top () {
    return this.data[1]
  }

  heapify (i) {
    while (true) {
      let min = i
      const [l, r, n] = [i * 2, i * 2 + 1, this.data.length]
      if (l < n && this.lt(l, min)) { min = l }
      if (r < n && this.lt(r, min)) { min = r }
      if (min !== i) {
        this.swap(i, min)
        i = min
      } else { break }
    }
  }

  swap (i, j) {
    const d = this.data;
    [d[i], d[j]] = [d[j], d[i]]
  }
}
