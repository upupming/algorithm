class ListNode {
  constructor (val = undefined, next = null) {
    this.value = val
    this.next = next
  }
}

// 头一次遇到 array 的 shift 的性能有问题的情况，不得不使用 Queue
class Queue1 {
  constructor (collection = []) {
    this.lead = new ListNode()
    this.tail = this.lead
    this._size = 0
    for (const item of collection) { this.push(item) }
  }

  size () {
    return this._size
  }

  push (value) {
    this.tail = this.tail.next = new ListNode(value)
    this._size++
  }

  back () {
    return this.tail.value
  }

  shift () {
    if (!this._size) { return undefined }
    const first = this.lead.next
    this.lead.next = first.next
    this._size--
    if (this._size === 0) { this.tail = this.lead }
    return first.value
  }

  front () {
    if (!this._size) { return undefined }
    return this.lead.next.value
  }

  * values () {
    let node = this.lead.next
    while (node) {
      yield node.value
      node = node.next
    }
  }
}

/**
 * @param {number[]} nums
 * @param {number} start
 * @param {number} goal
 * @return {number}
 */
const minimumOperations = function (nums, start, goal) {
  const q = new Queue1([start]); const p = new Set([]); const ops = {}
  ops[start] = 0
  while (q.size()) {
    const val = q.shift()
    if (p.has(val)) continue
    p.add(val)
    for (const x of nums) {
      let y = val + x
      if (!p.has(y) && y >= 0 && y <= 1000) {
        q.push(y)
        ops[y] = Math.min(ops[val] + 1, ops[y] ?? 1e10)
      }
      y = val - x
      if (!p.has(y) && y >= 0 && y <= 1000) {
        q.push(y)
        ops[y] = Math.min(ops[val] + 1, ops[y] ?? 1e10)
      }
      y = val ^ x
      if (!p.has(y) && y >= 0 && y <= 1000) {
        q.push(y)
        ops[y] = Math.min(ops[val] + 1, ops[y] ?? 1e10)
      }
    }
  }

  if (goal >= 0 && goal <= 1000) {
    if (p.has(goal)) return ops[goal]
    else return -1
  }
  for (const val of p) {
    for (const x of nums) {
      if ((val + x === goal) || (val - x === goal) || ((val ^ x) === goal)) {
        // console.log(val, ops[val], x, val + x, val - x, val ^ x, goal, (val + x === goal) , (val - x === goal) , (val ^ x === goal))
        return ops[val] + 1
      }
    }
  }
  return -1
}
/**
 * [-17]
96
79
[-31,15,23,43,56,21,-65,45,22,-85]
68
-42
[70,83,-93,47,-81,94,64,84,4,28,37,99,42,74]
95
-25
 */
