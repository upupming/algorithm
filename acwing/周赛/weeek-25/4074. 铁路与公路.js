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
let _Queue_size
Object.defineProperty(exports, '__esModule', { value: true })
exports.Queue = exports.ListNode = void 0
class ListNode {
  constructor (val = undefined, next = null) {
    this.value = val
    this.next = next
  }
}
exports.ListNode = ListNode
class Queue {
  constructor (collection = []) {
    _Queue_size.set(this, void 0)
    this.lead = new ListNode()
    this.tail = this.lead
    __classPrivateFieldSet(this, _Queue_size, 0, 'f')
    for (const item of collection) { this.push(item) }
  }

  size () {
    return __classPrivateFieldGet(this, _Queue_size, 'f')
  }

  push (value) {
    this.tail = this.tail.next = new ListNode(value)
    __classPrivateFieldSet(this, _Queue_size, +__classPrivateFieldGet(this, _Queue_size, 'f') + 1, 'f')
  }

  back () {
    return this.tail.value
  }

  shift () {
    if (!__classPrivateFieldGet(this, _Queue_size, 'f')) { return undefined }
    const first = this.lead.next
    this.lead.next = first.next
    __classPrivateFieldSet(this, _Queue_size, +__classPrivateFieldGet(this, _Queue_size, 'f') - 1, 'f')
    if (__classPrivateFieldGet(this, _Queue_size, 'f') === 0) { this.tail = this.lead }
    return first.value
  }

  front () {
    if (!__classPrivateFieldGet(this, _Queue_size, 'f')) { return undefined }
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
exports.Queue = Queue
_Queue_size = new WeakMap()

let input = ''

process.stdin.on('data', (data) => {
  input += data
})

process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [n, m] = lines[0].split(' ').map(Number)
  const e = [...Array(n + 1)].map(() => new Set())
  for (let i = 1; i <= m; i++) {
    const [u, v] = lines[i].split(' ').map(Number)
    e[u].add(v); e[v].add(u)
  }
  const e1 = [...Array(n + 1)].map(() => new Set())
  for (let i = 1; i <= n; i++) {
    for (let j = 1; j <= n; j++) {
      if (j === i) continue
      if (!e[i].has(j)) e1[i].add(j)
    }
  }
  const d = []; const v = []
  const set = (d, [i, j], val) => {
    d[i] = d[i] || []
    d[i][j] = val
  }
  const get = (d, [i, j]) => d[i] == null ? undefined : d[i][j]
  const s = [1, 1]
  set(d, s, 0); set(v, s, 1)
  const q = new Queue()
  q.push(s)
  while (q.size()) {
    const [x, y] = q.shift()
    if (x === n && y === n) {
      console.log(get(d, [x, y]))
      return
    }
    set(v, [x, y], 0)
    // 暗藏玄机：必定有一条路是直接从 1 到 n 的
    if (!(x === n || y === n) && !(x === 1 || y === 1)) continue
    for (const nx of (x === n ? [n] : e[x])) {
      for (const ny of (y === n ? [n] : e1[y])) {
        if (nx === ny && nx !== n) continue
        let dn = get(d, [nx, ny])
        if (dn === undefined) dn = Infinity
        const dCurrent = get(d, [x, y])
        // console.log(x, y, nx, ny, dn, dCurrent)
        if (dn > dCurrent + 1) {
          set(d, [nx, ny], dCurrent + 1)
          if (!get(v, [nx, ny])) {
            q.push([nx, ny])
            set(v, [nx, ny], 1)
          }
        }
      }
    }
  }
  console.log(-1)
})
