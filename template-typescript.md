# 算法模板（JS/TS 版本）

> 为了训练自己的 JavaScript/TypeScript 编程能力，能用 TS 写的地方尽量用，不行再换 C++

- [算法模板（JS/TS 版本）](#算法模板jsts-版本)
    - [输入](#输入)
        - [`readline` 输入](#readline-输入)
        - [`process.stdin.on` 输入](#processstdinon-输入)
        - [fs 输入](#fs-输入)
    - [常用函数缩写](#常用函数缩写)
    - [快速幂](#快速幂)
    - [邻接表](#邻接表)
    - [快速幂](#快速幂-1)
    - [并查集](#并查集)
    - [拓扑排序](#拓扑排序)
    - [字符串哈希](#字符串哈希)
    - [线段树](#线段树)
        - [单点修改](#单点修改)
        - [区间修改](#区间修改)
        - [同时支持单点修改和区间修改](#同时支持单点修改和区间修改)

## 输入

JS 的输入输出是一个和 C++ 完全不同，需要从思维上进行转变，相当于是拿到整体全部的输入之后再处理比较方便。

[Node.js 环境](https://www.jianshu.com/p/70a04abd0823)下常用的有 `readline` 和 `process.stdin.on` 两种方法。[V8](https://codeforces.com/blog/entry/77741) 则是 `readline` 和 `print`。

最大的缺点是，一行数据读进来之后，需要自己进行 `split` 并转换成自己想要的数据类型。代码写起来不够优雅。

推荐使用 `process.stdin.on` 这种输入方法。

### `readline` 输入

- 缺点: 输入是被动的（回调函数）。不能主动控制当前的输入进度，比如第一行要输入数字，第二行要输入字符串，那么就需要判断当前输入时第几行，处理起来较为麻烦。

```ts
import readline = require('readline')

let countLine = 0
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
})
rl.on('line', function (line) {
  const tokens = line.split(' ')
  console.log(parseInt(tokens[0]) + parseInt(tokens[1]))
  if (++countLine === 10) {
    console.log('当前输入的是第 10 行')
  }
})

```

### `process.stdin.on` 输入

- 优点: 通过 `data` 事件逐渐累积数据，最后到 `end` 的时候统一处理，看上去像是主动处理所有的数据（但本质上还是回调函数）。
- 缺点: `end` 在手动输入的情况下无法触发，因此需要加 `SIGINT`，利用 `Ctrl+C` 来触发结束命令。

```ts
let input = ''
process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})
process.on('SIGINT', function () {
  main()
})

function main () {
  const inputArray = input.split('\n')
  console.log(inputArray)
}

```

Update: 有些 OJ (AcWing) 不支持 `'/dev/stdin'`，最简洁的办法就是：

```js
let input = ''
let lines
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  lines = input.split('\n')
  main()
})

function main () {
  console.log(lines)
}

```

### fs 输入

参考 [node-scanf](https://github.com/Lellansin/node-scanf/blob/1fd4eb96bbe26c5c22edc3b72b5aa2fdbc591866/lib/gets.js#L11) 和 [node.js: readSync from stdin?](https://stackoverflow.com/questions/3430939/node-js-readsync-from-stdin/9318276)。

- 优点: 输入是主动的（不是回调函数）
- 缺点: 还是得全部输入之后再做处理（因为不能要求 `readFileSync` 只读一行，`readFileSync` 有自己的缓冲机制，你最多只能传一个 `buf` 给他，但是每次 `readFileSync` 得到的不一定是一行输入，在文件输入的情况下常常可能是多行，手动输入才可能是一行），使用上和 process.stdin.on 是等价的

> node-scanf 是自己实现了一套缓冲和读取逻辑，比较复杂，代码太长了，不适合复制过来使用

```ts
import fs = require('fs')
const input = fs.readFileSync('/dev/stdin').toString()
const inputArray = input.split('\n')
console.log(inputArray)

```

## 常用函数缩写

```ts
const _max = Math.max.bind(Math)
const _min = Math.min.bind(Math)
const _pow = Math.pow.bind(Math)
const _floor = Math.floor.bind(Math)
const _round = Math.round.bind(Math)
const _ceil = Math.ceil.bind(Math)
const log = console.log.bind(console)
// const log = (...args: any[]) => {}

作者：我不吃饼干呀
链接：https://juejin.cn/post/6844903876206805005
来源：掘金
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

## 快速幂

```ts
// 有一个坑的点是 (1e9+7)^2 在 JS 里面会溢出，会在 ans * a 就产生溢出
// 遇到 1e9+7 的题目最好全部用 BigInt，避免产生溢出问题
function pow (a1: number, b1: number, p1: number) {
  let a = BigInt(a1); let b = BigInt(b1); const p = BigInt(p1)
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return Number(ans)
}

function pow (a: bigint, b: bigint, p: bigint) {
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return ans
}
```

## 邻接表

> 因为 JS 里面没有静态数组，所以用数组模拟邻接表没有意义，这个方法显得有些鸡肋

```ts
const head = new Array<number>(n + 1).fill(0)
const ver = new Array<number>(m + 1).fill(0)
const edge = new Array<number>(m + 1).fill(0)
const next = new Array<number>(m + 1).fill(0)
let tot = 0
function add (x: number, y: number, z: number) {
  ver[++tot] = y
  edge[tot] = z
  next[tot] = head[x]
  head[x] = tot
}

for (const e of edges) {
  add(e[0], e[1], e[2])
  add(e[1], e[0], e[2])
}
for (let i = head[x]; i; i = next[x]) {
  const [y, z]  = [ver[i], edge[i]]
}
```

## 快速幂

```ts
function qpow (a: bigint, b: bigint, p: bigint) {
  let ans = 1n % p
  while (b) {
    if (b & 1n) ans = ans * a % p
    a = a * a % p
    b >>= 1n
  }
  return ans
}
```

## 并查集

```ts
const fa = [...Array<number>(n)].map((_, idx) => idx)
function get (x: number): number {
  if (x === fa[x]) return x
  return fa[x] = get(fa[x])
}
function merge (x: number, y: number) {
  const fx = get(x); const fy = get(y)
  fa[fx] = fy
}
```

```js
const fa = [...Array(n)].map((_, idx) => idx)
function get (x) {
  if (x === fa[x]) return x
  return fa[x] = get(fa[x])
}
function merge (x, y) {
  const fx = get(x); const fy = get(y)
  fa[fx] = fy
}
```

## 拓扑排序

```ts
// LeetCode 210. Course Schedule II
function findOrder(n: number, p: number[][]): number[] {
    const e = [...Array(n)].map(() => []), deg = Array(n).fill(0)
    const ans = [], q = []
    for (const [a, b] of p) {
        e[b].push(a)
        deg[a]++
    }
    for (let i = 0; i < n; i++) if (deg[i] === 0) q.push(i)
    while (q.length) {
        const x = q.shift()
        ans.push(x)
        for (const y of e[x]) {
            if (--deg[y] === 0) {
                q.push(y)
            }
        }
    }
    return ans.length === n ? ans : []
};
```

## 字符串哈希

```js
// 最好以 1 为开始下标，比较好处理 p 数组
const n = s.length
s = ' ' + s

const P = 131n
const Q = 1n << 64n
const f = [0n]; const p = [1n]
for (let i = 1; i <= n; i++) {
  f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)))) % Q
  p[i] = p[i - 1] * P % Q
}
const hash = (i, j) => {
  // 乘完之后的取模非常重要，漏掉就会 WA（出现较小负数导致 + 一个 Q 不够）
  return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
}
```

## 线段树

统一使用动态开点线段树。

### 单点修改

> https://leetcode.com/problems/longest-substring-of-one-repeating-character/

```ts
class Node {
  start: number
  end: number
  maxLen: number[]
  leftMaxLen: number[]
  rightMaxLen: number[]
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
    this.maxLen = Array(26).fill(0)
    this.leftMaxLen = Array(26).fill(0)
    this.rightMaxLen = Array(26).fill(0)
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (pos: number, char: string) {
    this.modifyNode(this.root, pos, char)
  }

  modifyNode (node: Node, pos: number, char: string) {
    if (node.start === pos && node.end === pos) {
      for (let i = 0; i < 26; i++) {
        node.leftMaxLen[i] = node.rightMaxLen[i] = node.maxLen[i] = char === (String.fromCharCode('a'.charCodeAt(0) + i)) ? 1 : 0
      }
    } else {
      this.pushdown(node)
      if (pos <= node.left!.end) this.modifyNode(node.left!, pos, char)
      if (pos >= node.right!.start) this.modifyNode(node.right!, pos, char)
      this.pushup(node)
    }
  }

  // 这里 pushdown 的作用只是动态创建新节点
  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
  }

  pushup (node: Node) {
    for (let i = 0; i < 26; i++) {
      node.leftMaxLen[i] = node.left!.leftMaxLen[i]
      if (node.left!.leftMaxLen[i] === node.left!.end - node.left!.start + 1) {
        node.leftMaxLen[i] = node.left!.leftMaxLen[i] + node.right!.leftMaxLen[i]
      }

      node.rightMaxLen[i] = node.right!.rightMaxLen[i]
      if (node.right!.rightMaxLen[i] === node.right!.end - node.right!.start + 1) {
        node.rightMaxLen[i] = node.right!.rightMaxLen[i] + node.left!.rightMaxLen[i]
      }

      node.maxLen[i] = Math.max(node.left!.maxLen[i], node.right!.maxLen[i], node.left!.rightMaxLen[i] + node.right!.leftMaxLen[i])
    }
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  arrayAdd (a: number[], b: number[]) {
    for (let i = 0; i < a.length; i++) a[i] += b[i]
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return node.maxLen

    this.pushdown(node)
    const sum = Array(26)
    if (start <= node.left!.end) this.arrayAdd(sum, this.queryNode(node.left!, start, end))
    if (end >= node.right!.start) this.arrayAdd(sum, this.queryNode(node.right!, start, end))
    return sum
  }
}

```

> https://leetcode.com/problems/booking-concert-tickets-in-groups/

```ts
class Node {
  start: number
  end: number
  max: number
  sum: number
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
    this.max = 0
    this.sum = 0
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (pos: number, val: number) {
    this.modifyNode(this.root, pos, val)
  }

  modifyNode (node: Node, pos: number, val: number) {
    if (node.start === pos && node.end === pos) {
      node.max = node.sum = val
    } else {
      this.pushdown(node)
      if (pos <= node.left!.end) this.modifyNode(node.left!, pos, val)
      if (pos >= node.right!.start) this.modifyNode(node.right!, pos, val)
      this.pushup(node)
    }
  }

  // 这里 pushdown 的作用只是动态创建新节点
  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
  }

  pushup (node: Node) {
    node.max = Math.max(node.left!.max, node.right!.max)
    node.sum = node.left!.sum + node.right!.sum
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return [node.max, node.sum]

    this.pushdown(node)
    let max = 0; let sum = 0
    if (start <= node.left!.end) {
      const [_m, _s] = this.queryNode(node.left!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    if (end >= node.right!.start) {
      const [_m, _s] = this.queryNode(node.right!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    return [max, sum]
  }
}

```

### 区间修改

> https://leetcode.com/problems/range-module/

```ts
enum Tracked {
  TRUE = 'TRUE',
  FALSE = 'FALSE'
}

class Node {
  start: number
  end: number
  val: number = 0
  lazy: Tracked | null = null
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (start: number, end: number, tracked: boolean) {
    this.modifyNode(this.root, start, end, tracked)
  }

  modifyNode (node: Node, start: number, end: number, tracked: boolean) {
    if (start <= node.start && end >= node.end) {
      node.val = tracked ? (node.end - node.start + 1) : 0
      node.lazy = tracked ? Tracked.TRUE : Tracked.FALSE
    } else {
      this.pushdown(node)
      // pushdown 已经确保 left 和 right 一定存在了
      if (start <= node.left!.end) this.modifyNode(node.left!, start, end, tracked)
      if (end >= node.right!.start) this.modifyNode(node.right!, start, end, tracked)
      this.pushup(node)
    }
  }

  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
    if (node.lazy) {
      node.left.lazy = node.lazy
      node.left.val = (node.lazy === Tracked.TRUE) ? (node.left.end - node.left.start + 1) : 0

      node.right.lazy = node.lazy
      node.right.val = (node.lazy === Tracked.TRUE) ? (node.right.end - node.right.start + 1) : 0

      node.lazy = null
    }
  }

  pushup (node: Node) {
    node.val = node.left!.val + node.right!.val
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return node.val

    this.pushdown(node)
    let sum = 0
    if (start <= node.left!.end) sum += this.queryNode(node.left!, start, end)
    if (end >= node.right!.start) sum += this.queryNode(node.right!, start, end)
    return sum
  }
}

```

### 同时支持单点修改和区间修改

写法比较复杂，如果题目只需要单点修改就行了，可以对单点修改拓展，忽略区间修改方法。

> https://leetcode.com/problems/booking-concert-tickets-in-groups

```ts
class Node {
  start: number
  end: number
  max: number = 0
  sum: number = 0
  lazy: number | null = null
  left: null | Node = null
  right: null | Node = null
  constructor (start: number, end: number) {
    this.start = start
    this.end = end
  }
}

// https://www.acwing.com/activity/content/code/content/167900/
class SegmentTree {
  root: Node
  constructor (start: number, end: number) {
    this.root = new Node(start, end)
  }

  modify (pos: number, val: number) {
    this.modifyNode(this.root, pos, val)
  }

  modifyNode (node: Node, pos: number, val: number) {
    if (node.start === pos && node.end === pos) {
      node.max = node.sum = val
    } else {
      this.pushdown(node)
      if (pos <= node.left!.end) this.modifyNode(node.left!, pos, val)
      if (pos >= node.right!.start) this.modifyNode(node.right!, pos, val)
      this.pushup(node)
    }
  }

  // 使用 modify 和 modifyRange 是等价的，modifyRange 更加通用
  modifyRange (start: number, end: number, val: number) {
    this.modifyNodeRange(this.root, start, end, val)
  }

  modifyNodeRange (node: Node, start: number, end: number, val: number) {
    if (start <= node.start && end >= node.end) {
      node.sum = val * (end - start + 1)
      node.max = val
      node.lazy = val
    } else {
      this.pushdown(node)
      if (start <= node.left!.end) this.modifyNodeRange(node.left!, start, end, val)
      if (end >= node.right!.start) this.modifyNodeRange(node.right!, start, end, val)
      this.pushup(node)
    }
  }

  // 这里 pushdown 同时保证了 left, right 一定存在
  pushdown (node: Node) {
    const mid = node.start + node.end >> 1
    node.left ??= new Node(node.start, mid)
    node.right ??= new Node(mid + 1, node.end)
    if (node.lazy != null) {
      node.left.lazy = node.lazy
      node.left.max = node.lazy
      node.left.sum = node.lazy * (node.left.end - node.left.start + 1)

      node.right.lazy = node.lazy
      node.right.max = node.lazy
      node.right.sum = node.lazy * (node.right.end - node.right.start + 1)

      node.lazy = null
    }
  }

  pushup (node: Node) {
    node.max = Math.max(node.left!.max, node.right!.max)
    node.sum = node.left!.sum + node.right!.sum
  }

  query (start: number, end: number) {
    return this.queryNode(this.root, start, end)
  }

  queryNode (node: Node, start: number, end: number) {
    if (start <= node.start && end >= node.end) return [node.max, node.sum]

    this.pushdown(node)
    let max = 0; let sum = 0
    if (start <= node.left!.end) {
      const [_m, _s] = this.queryNode(node.left!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    if (end >= node.right!.start) {
      const [_m, _s] = this.queryNode(node.right!, start, end)
      max = Math.max(max, _m)
      sum += _s
    }
    return [max, sum]
  }
}

```
