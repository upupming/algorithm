class SnapshotArray {
  // snap[i]: list of [snap_id, snap_value]
  _snap: Array<Array<[number, number]>>
  a: number[]
  cnt = 0
  changed: Set<number>
  constructor (length: number) {
    this._snap = Array(length).fill(0).map(() => [])
    this.a = Array(length).fill(0)
    this.changed = new Set(Array(length).fill(0).map((_, idx) => idx))
  }

  set (index: number, val: number): void {
    this.a[index] = val
    this.changed.add(index)
  }

  snap (): number {
    for (const idx of this.changed) {
      this._snap[idx].push([this.cnt, this.a[idx]])
    }
    this.changed.clear()
    return this.cnt++
  }

  get (index: number, snap_id: number): number {
    const n = this._snap[index].length
    let l = 0; let r = n - 1
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (this._snap[index][mid][0] <= snap_id) l = mid
      else r = mid - 1
    }
    return this._snap[index][l][1]
  }
}

/**
* Your SnapshotArray object will be instantiated and called as such:
* var obj = new SnapshotArray(length)
* obj.set(index,val)
* var param_2 = obj.snap()
* var param_3 = obj.get(index,snap_id)
*/
