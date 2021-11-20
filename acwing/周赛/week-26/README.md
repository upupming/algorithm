# AcWing Week 26 题解

- [AcWing Week 26 题解](#acwing-week-26-题解)
    - [4076. 字符串权值](#4076-字符串权值)
    - [4077. k显性字符](#4077-k显性字符)
        - [算法 —— 二分 + 前缀和](#算法--二分--前缀和)
        - [JS 代码](#js-代码)
    - [4078. 01串](#4078-01串)
        - [算法 —— 记忆化搜索 + 前缀和](#算法--记忆化搜索--前缀和)
        - [JS 代码](#js-代码-1)

## 4076. 字符串权值

模拟题，直接上代码。

## 4077. k显性字符

### 算法 —— 二分 + 前缀和

- 二分所有的 `k`，`k` 最小是 1，最大是字符串总长度 `n`
- 对于每一个长度 `len` 需要从头到尾扫描所有长度为 `len` 的区间，判断区间内是否有同样的一个字符 `c`，因为最多只有 26 个字符，直接暴力枚举所有可能的 `c`，只要有一个 `c` 是满足就可以
    - 利用前缀和数组 `cnt[i][j]` 存储字符 `i` 在 `1~j` 区间出现的次数，可以让针对某个区间的判断时间复杂度降低为 `O(1)`
- 总时间复杂度: `O(n log n)`
    - 与计算 `cnt` 数组: `O(26n)`
    - 二分 `k`: `O(log n)`
        - 判断是否满足条件: `O(n)`

### JS 代码

```js
let input = ''

process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const s = input.split('\n')[0]
  const n = s.length
  const t = ('#' + s).split('').map(ch => ch.charCodeAt(0) - 'a'.charCodeAt(0))
  let [l, r] = [1, n]
  const cnt = [...Array(26)].map(() => Array(n + 1).fill(0))
  for (let i = 0; i < 26; i++) {
    for (let j = 1; j <= n; j++) {
      cnt[i][j] = cnt[i][j - 1] + (t[j] === i)
    }
  }

  const valid = (len) => {
    // 所有长为 len 的都至少存在一个字符 i
    for (let i = 0; i < 26; i++) {
      let ok = true
      for (let j = 1; j + len - 1 <= n; j++) {
        const k = j + len - 1
        const x = cnt[i][k] - cnt[i][j - 1]
        if (x <= 0) {
          ok = false
          break
        }
      }
      if (ok) return true
    }
    return false
  }
  while (l < r) {
    const mid = l + r >> 1
    if (valid(mid)) r = mid
    else l = mid + 1
  }
  console.log(l)
})

```

## 4078. 01串

### 算法 —— 记忆化搜索 + 前缀和

我是先暴力写了一个 `select(n, k)` 函数表示长度为 `n` 的字符，在题意中 `k` 的条件下，有多少可能的情况，暴力枚举的，然后找了一下规律：

```js
function select (n, k) {
  let ans = 0
  for (let i = 0; i < 1 << n; i++) {
    let isSuit = true
    for (let j = 0; j < n; j++) {
      // 后面 k 位必须都是 1
      if (i >> j & 1) {
        let bits = 0
        for (let l = j; l <= j + k - 1; l++) {
          if ((i >> l & 1)) bits++
        }
        if (bits !== k) {
          isSuit = false
          break
        }
        j = j + k - 1
      }
    }
    ans += isSuit
  }

  return ans
}
```

```bash
n k select(n, k)

1 2 1
2 2 2
3 2 3
4 2 5
5 2 8
6 2 13
7 2 21
8 2 34
9 2 55
10 2 89

1 3 1
2 3 1
3 3 2
4 3 3
5 3 4
6 3 6
7 3 9
8 3 13
9 3 19
10 3 28

1 4 1
2 4 1
3 4 1
4 4 2
5 4 3
6 4 4
7 4 5
8 4 7
9 4 10
10 4 14
```

找到递推公式：

```txt
select(n, k) = select(n - 1, k) + select(n - k, k)
```

- 有了递推公式就可以做了，利用记忆化搜索写起来对边界情况处理简单一些。
- 然后就是需要求一个前缀和 `pre[i]` 表示长度 `n` 为 `1~i` 里面所有满足条件的串的总数。
- 最后每次查询的答案就是 `pre[r] - pre[l - 1]`
- 时间复杂度
    - 计算所有的 select(n, k): `O(max(r))`
    - 计算 pre 数组: `O(max(r))`
    - T 次查询: `O(T)`
    - 总时间复杂度是 `O(T + max(r))`

### JS 代码

```js
function select (n, k) {
  let ans = 0
  for (let i = 0; i < 1 << n; i++) {
    let isSuit = true
    for (let j = 0; j < n; j++) {
      // 后面 k 位必须都是 1
      if (i >> j & 1) {
        let bits = 0
        for (let l = j; l <= j + k - 1; l++) {
          if ((i >> l & 1)) bits++
        }
        if (bits !== k) {
          isSuit = false
          break
        }
        j = j + k - 1
      }
    }
    ans += isSuit
  }

  return ans
}

const cache = []
const P = 1e9 + 7

function select_optimized (n, k) {
  if (cache[n] == undefined)cache[n] = []
  if (cache[n][k] !== undefined) return cache[n][k]

  let ans = 0

  if (n < k) ans = 1
  else if (n === k) ans = 2
  else {
    ans = (select_optimized(n - 1, k) + select_optimized(n - k, k)) % P
  }

  return cache[n][k] = ans
}

const pre = [0]

let input = ''
process.stdin.on('data', (data) => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t, k] = lines[0].split(' ').map(Number)
  for (let i = 1; i <= 1e5 + 10; i++) {
    pre[i] = (pre[i - 1] + select_optimized(i, k)) % P
  }
  for (let i = 1; i <= t; i++) {
    const [l, r] = lines[i].split(' ').map(Number)
    console.log((pre[r] - pre[l - 1] + P) % P)
  }
})

/*
for (let i = 1; i <= 10; i++) {
  console.log(i, 2, select(i, 2))
  console.assert(select(i, 2) === select_optimized(i, 2))
}
console.log()
for (let i = 1; i <= 10; i++) {
  console.log(i, 3, select(i, 3))
  console.assert(select(i, 3) === select_optimized(i, 3))
}
console.log()
for (let i = 1; i <= 10; i++) {
  console.log(i, 4, select(i, 4))
  console.assert(select(i, 4) === select_optimized(i, 4))
}
*/

```
