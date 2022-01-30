# LeetCode Contest 278

## 5993. Keep Multiplying Found Values by Two

### 算法 —— 模拟、暴力

- 先把数组存到一个 Set 里面
- 按照题目意思模拟即可，一直倍增当前数知道集合找不到

### 时间复杂度

- 每次倍增 2，最大值位 1000，最坏时间复杂度为 `log_2{1000}`

### JS 代码

```js
/**
 * @param {number[]} nums
 * @param {number} original
 * @return {number}
 */
const findFinalValue = function (nums, o) {
  const s = new Set(nums)
  while (s.has(o)) o *= 2
  return o
}

```

## 5981. All Divisions With the Highest Score of a Binary Array

### 算法 —— 前缀和

- 先求出 0 的个数、1 的个数的前缀和 `cnt0` 和 `cnt1`
- 接着枚举所有可能的 left 数组的长度，计算分数值
- 求出最大分数值，以及可以达到这个分数值的所有可能的 left 的长度

### 时间复杂度

- 前缀和: `O(n)`
- 后续处理: `O(n)`

### JS 代码

```js
/**
 * @param {number[]} nums
 * @return {number[]}
 */
const maxScoreIndices = function (nums) {
  const n = nums.length
  const cnt0 = [0]; const cnt1 = [0]; const score = []
  for (let i = 1; i <= n; i++) {
    cnt0[i] = cnt0[i - 1] + (nums[i - 1] === 0)
    cnt1[i] = cnt1[i - 1] + (nums[i - 1] === 1)
  }
  let max = 0; const ans = []
  for (let i = 0; i <= n; i++) {
    score[i] = cnt0[i] + cnt1[n] - cnt1[i]
    max = Math.max(max, score[i])
  }
  for (let i = 0; i <= n; i++) {
    if (score[i] === max) ans.push(i)
  }
  return ans
}

```

## 5994. Find Substring With Given Hash Value

### 算法 —— 字符串哈希

- 经典的字符串哈希模板题，但是我们平时求 Hash 的时候是从左往右算的，左边的是最高位，此题的意思则是右边是最高位，因此可以简单地对输入字符串 `s` 先翻转一下变成 `t`，求 `t` 的**最后一个**长为 `k` 的哈希值为 `hashValue` 的字符串。
- 在 JS 中 `MAX_SAFE_INTEGER=2^53-1`（9e15），因此 1e9 * 1e9 往往会溢出，需要使用 BigInt，如果是 C++ 则只需要使用 `long long` 就够了。

### 时间复杂度

- 预处理 `f` 和 `p` 数组: `O(n)`
- 对于每个下标，计算长为 k 的串的 hash 值，总共需要 `O(n-k)` 时间

### JS 代码

```js
/**
 * @param {string} s
 * @param {number} power
 * @param {number} modulo
 * @param {number} k
 * @param {number} hashValue
 * @return {string}
 */
const subStrHash = function (s, pp, m, k, h) {
  const n = s.length
  s = ' ' + s.split('').reverse().join('')

  const P = BigInt(pp)
  const Q = BigInt(m)
  const f = [0n]; const p = [1n]
  for (let i = 1; i <= n; i++) {
    f[i] = (f[i - 1] * P % Q + (BigInt(s[i].charCodeAt(0) - 'a'.charCodeAt(0)) + 1n)) % Q
    p[i] = p[i - 1] * P % Q
  }
  const getHash = (i, j) => {
    return (f[j] - f[i - 1] * p[j - i + 1] % Q + Q) % Q
  }
  let ans = ''
  for (let i = 1; i + k - 1 <= n; i++) {
    const j = i + k - 1
    const hash = getHash(i, j)
    if (hash === BigInt(h)) ans = s.slice(i, j + 1)
  }
  return ans.split('').reverse().join('')
}

```

## 5995. Groups of Strings

### 算法 —— 并查集+位运算

- 对于每个 `words[i]`，字母的顺序无所谓，只关心字母的存在与否，因此考虑使用位运算。
- 预处理 `m`，其中 `m[i]` 是一个 `[0, 1<<26)` 之间的数，二进制表示的第 j 位代表 `words[i]` 中是不是有字母 `j` 存在。
- 预处理 map，`map[key] = array`，其中 `array` 表示所有位运算表示为 `key` 的 word 的下标的集合，先把同一个 key 中所有 array 的元素合并到一起，因为这些下标代表的 word 字幕集合完全相同
- 对于每一个 word，位运算考虑 3 种情况，分别计算能够和它一组的位运算表示，并在 map 中查找对应的元素下标，进行合并操作

### 时间复杂度

- 预处理: `O(nm)`，其中 n 为 `words.length`，m 为 `words[i].length`
- 对于每个 word 进行寻找邻居和合并操作: O(`n * 26 * 26`)

### JS 代码

```js
/**
 * @param {string[]} words
 * @return {number[]}
 */
const groupStrings = function (w) {
  const n = w.length

  const map = {}

  const m = w.map((s, idx) => {
    let ans = 0
    for (const ch of s) {
      const j = ch.charCodeAt(0) - 'a'.charCodeAt(0)
      ans += 1 << j
    }
    map[ans] ??= []
    map[ans].push(idx)
    return ans
  })

  const fa = [...Array(n)].map((_, idx) => idx)
  const sz = Array(n).fill(1)
  function get (x) {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  function merge (x, y) {
    const fx = get(x); const fy = get(y)
    if (fx == fy) return
    if (sz[fx] < sz[fy]) {
      fa[fx] = fy
      sz[fy] += sz[fx]
    } else {
      fa[fy] = fx
      sz[fx] += sz[fy]
    }
  }

  for (const key of Object.keys(map)) {
    const vals = map[key]
    for (let i = 1; i < vals.length; i++) {
      merge(vals[i - 1], vals[i])
    }
  }

  for (let i = 0; i < n; i++) {
    const x = m[i]
    for (let j = 0; j < 26; j++) {
      // 设为 1
      const y = x | (1 << j)
      // 设为 0
      let z = x
      if (z >> j & 1) z -= 1 << j
      for (const val of [y, z]) {
        if (map[val]) {
          merge(map[val][0], i)
        }
      }

      if (x >> j & 1) {
        // 尝试将 j 位换成别的
        for (let k = 0; k < 26; k++) {
          if ((x >> k & 1) === 0) {
            const val = x - (1 << j) + (1 << k)
            if (map[val]) {
              if (map[val]) {
                merge(map[val][0], i)
              }
            }
          }
        }
      }
    }
  }

  const ans = []; let max = 0
  for (let i = 0; i < n; i++) {
    if (get(i) === i) ans.push(i), max = Math.max(sz[i], max)
  }
  return [ans.length, max]
}

```
