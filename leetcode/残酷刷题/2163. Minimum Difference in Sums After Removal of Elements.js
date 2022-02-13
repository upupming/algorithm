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

/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumDifference = function (nums) {
  const n = nums.length / 3
  const lMin = []; const rMax = []
  let h = new Heap((a, b) => a > b); let s = 0
  for (let i = 0; i < 3 * n; i++) {
    h.push(nums[i]), s += nums[i]
    if (h.size() > n) s -= h.pop()
    if (h.size() === n) lMin[i] = s
  }
  h = new Heap(), s = 0
  for (let i = 3 * n - 1; i >= 0; i--) {
    h.push(nums[i]), s += nums[i]
    if (h.size() > n) s -= h.pop()
    if (h.size() === n) rMax[i] = s
  }
  let ans = 1e11
  for (let i = 0; i + 1 < 3 * n; i++) {
    if (lMin[i] == null || rMax[i + 1] == null) continue
    // console.log(i, lMin[i], rMax[i+1])
    ans = Math.min(ans, lMin[i] - rMax[i + 1])
  }
  return ans
}
