'use strict'
const __classPrivateFieldSet = (this && this.__classPrivateFieldSet) || function (receiver, state, value, kind, f) {
  if (kind === 'm') throw new TypeError('Private method is not writable')
  if (kind === 'a' && !f) throw new TypeError('Private accessor was defined without a setter')
  if (typeof state === 'function' ? receiver !== state || !f : !state.has(receiver)) throw new TypeError('Cannot write private member to an object whose class did not declare it')
  return (kind === 'a' ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value)), value
}
const __classPrivateFieldGet = (this && this.__classPrivateFieldGet) || function (receiver, state, kind, f) {
  if (kind === 'a' && !f) throw new TypeError('Private accessor was defined without a getter')
  if (typeof state === 'function' ? receiver !== state || !f : !state.has(receiver)) throw new TypeError('Cannot read private member from an object whose class did not declare it')
  return kind === 'm' ? f : kind === 'a' ? f.call(receiver) : f ? f.value : state.get(receiver)
}
let _RemovableHeap_instances, _RemovableHeap_invalidCount, _RemovableHeap_count, _RemovableHeap_normalize
Object.defineProperty(exports, '__esModule', { value: true })
exports.RemovableDoubleHeap = exports.RemovableHeap = exports.Heap = void 0
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
    while ((i >> 1 !== 0) && this.lt(i, i >> 1)) { this.swap(i, i >>= 1) }
  }

  pop () {
    this.swap(1, this.size())
    const top = this.data.pop()
    this.heapify(1)
    return top
  }

  top () { return this.data[1] }
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
 * @param {number} n
 * @param {number[][]} meetings
 * @param {number} firstPerson
 * @return {number[]}
 */
const findAllPeople = function (n, mt, fp) {
  const m = mt.length
  const ans = new Set()

  const e = []
  for (const m of mt) {
    const [a, b, w] = m
    e[a] ??= [], e[b] ??= []
    e[a].push({ p: b, w })
    e[b].push({ p: a, w })
  }
  e[0] ??= [], e[0].push({ p: fp, w: 0 })
  e[fp] ??= [], e[fp].push({ p: 0, w: 0 })
  const q = new Heap([{ p: 0, w: 0 }], (l, r) => l.w < r.w)
  const v = []
  while (q.size()) {
    const { p: cur, w: time } = q.pop()
    // console.log(cur)
    if (!ans.has(cur)) ans.add(cur)
    for (const y of e[cur]) {
      // console.log(cur, y, w, !v[y] && w >= time)
      if (y.w >= time) {
        if (v[y.p] == null) v[y.p] = y.w, q.push(y)
        else {
          if (y.w < v[y.p]) v[y.p] = y.w, q.push(y)
        }
      }
    }
  }

  return [...ans]
}
