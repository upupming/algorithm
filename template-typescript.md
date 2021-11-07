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

## 输入

JS 的输入输出是一个大坑，远不像 C++ 那么方便，[Node.js 环境](https://www.jianshu.com/p/70a04abd0823)下常用的有 `readline` 和 `process.stdin.on` 两种方法。[V8](https://codeforces.com/blog/entry/77741) 则是 `readline` 和 `print`。

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
function pow (a: number, b: number, p: number) {
  let ans = 1 % p
  while (b) {
    if (b & 1) ans = Number(BigInt(ans) * BigInt(a) % BigInt(p))
    a = Number(BigInt(a) * BigInt(a) % BigInt(p))
    b >>= 1
  }
  return ans
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
