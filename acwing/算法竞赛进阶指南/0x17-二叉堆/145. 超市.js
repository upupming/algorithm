class Heap {
  constructor (data = [], cmp = (a, b) => a < b) {
    if (typeof data === 'function') {
      cmp = data
      data = []
    }
    // heap 的数据一般从 1 开始索引，这样计算父亲、儿子节点更加简单
    this.data = [null]
    this.lt = (i, j) => cmp(this.data[i], this.data[j])
    data.forEach(this.push)
  }

  swap (i, j) {
    [this.data[i], this.data[j]] = [this.data[j], this.data[i]]
  }

  up (p) {
    while (p > 1) {
      if (this.lt(p, ~~(p / 2))) {
        this.swap(p, ~~(p / 2))
        p = ~~(p / 2)
      } else break
    }
  }

  down (p) {
    let s = p * 2
    while (s <= this.size()) {
      // 左右子节点取较小的（最小堆）/较大的（最大堆）
      if (s < this.size() && this.lt(s + 1, s)) s++
      // 子节点小于父亲节点，不满足最小堆性质
      if (this.lt(s, p)) {
        this.swap(s, p)
        p = s
        s = p * 2
      } else break
    }
  }

  remove (p) {
    this.swap(p, this.size())
    const val = this.data.pop()
    this.up(p)
    this.down(p)
    return val
  }

  size () {
    return this.data.length - 1
  }

  push (val) {
    this.data.push(val)
    this.up(this.size())
  }

  pop () {
    this.swap(1, this.size())
    const val = this.data.pop()
    this.down(1)
    return val
  }

  top () {
    return this.data[1]
  }
}

let input = ''
process.stdin.on('data', data => {
  input += data
})
process.stdin.on('end', () => {
  const arr = input.replace(/\n/g, ' ').split(' ').filter(s => s !== '').map(Number)
  // console.log(arr)
  // const iterator = arr[Symbol.iterator]()
  // console.log(arr)
  // console.log(iterator.next())
  let i = 0
  while (i < arr.length) {
    const n = arr[i++]
    const heap = new Heap()
    const pd = []
    for (let j = 0; j < n; j++) {
      pd.push([arr[i++], arr[i++]])
    }
    // 按照过期时间排序，保证插入到堆中的时候，堆中已经存在的商品的过期时间不会大于当前商品的过期时间
    pd.sort((a, b) => a[1] - b[1])
    for (let j = 0; j < n; j++) {
      const [p, d] = [pd[j][0], pd[j][1]]
      if (d > heap.size()) {
        heap.push(p)
      } else if (d === heap.size()) {
        if (heap.top() < p) {
          heap.pop()
          heap.push(p)
        }
      }
      // console.log(p, d, heap.data)
    }
    console.log(heap.data.slice(1).reduce((p, c) => p + c, 0))
  }
})
