# LeetCode 周赛 368 题解

> 好久没打周赛了，这次周赛题目难度还是不小的，没有做完hh，赛后补了第四题

## 100106. Minimum Sum of Mountain Triplets I

### 题目

You are given a **0-indexed** array `nums` of integers.

A triplet of indices `(i, j, k)` is a **mountain** if:

- `i < j < k`
- `nums[i] < nums[j]` and `nums[k] < nums[j]`

Return _the **minimum possible sum** of a mountain triplet of_ `nums`. _If no such triplet exists, return_ `-1`.

**Example 1:**

**Input:** nums = \[8,6,1,5,3\]
**Output:** 9
**Explanation:** Triplet (2, 3, 4) is a mountain triplet of sum 9 since:
- 2 < 3 < 4
- nums\[2\] < nums\[3\] and nums\[4\] < nums\[3\]
And the sum of this triplet is nums\[2\] + nums\[3\] + nums\[4\] = 9. It can be shown that there are no mountain triplets with a sum of less than 9.

**Example 2:**

**Input:** nums = \[5,4,8,7,10,2\]
**Output:** 13
**Explanation:** Triplet (1, 3, 5) is a mountain triplet of sum 13 since:
- 1 < 3 < 5
- nums\[1\] < nums\[3\] and nums\[5\] < nums\[3\]
And the sum of this triplet is nums\[1\] + nums\[3\] + nums\[5\] = 13. It can be shown that there are no mountain triplets with a sum of less than 13.

**Example 3:**

**Input:** nums = \[6,5,4,3,4,5\]
**Output:** -1
**Explanation:** It can be shown that there are no mountain triplets in nums.

**Constraints:**

- `3 <= nums.length <= 50`
- `1 <= nums[i] <= 50`

### 算法——暴力枚举

- 暴力枚举三元组，判断是否满足山形条件，满足则更新最小值
- 算法复杂度
    - 时间复杂度：O(n^3)
    - 空间复杂度：O(1)

### JS 代码

```js
/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumSum = function (nums) {
  const n = nums.length
  let ans = 1e10
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      for (let k = j + 1; k < n; k++) {
        if (nums[i] < nums[j] && nums[j] > nums[k]) ans = Math.min(ans, nums[i] + nums[j] + nums[k])
      }
    }
  }
  return ans === 1e10 ? -1 : ans
}

```

## 100114. Minimum Sum of Mountain Triplets II

### 题目

同上，仅数据范围发生变化。

**Constraints:**

- `3 <= nums.length <= 10<sup>5</sup>`
- `1 <= nums[i] <= 10<sup>8</sup>`

### 算法——前缀后缀最小值

- 前缀后缀最小值，分别用 `minA` 和 `minB` 存储。
- 对于 `j`，找到索引 `<j` 的最小值 `minA[j-1]` 和索引 `>j` 的最小值 `minB[j+1]`，如果 `minA[j-1] < nums[j] && minB[j+1] < nums[j]`，则更新最小值。
- 算法复杂度
    - 时间复杂度：O(n)
    - 空间复杂度：O(n)

### JS 代码

```js
/**
 * @param {number[]} nums
 * @return {number}
 */
const minimumSum = function (nums) {
  const n = nums.length; let ans = 1e10
  const minA = Array(n).fill(1e10); const minB = Array(n).fill(1e10)
  minA[-1] = 1e10, minB[n] = 1e10
  for (let i = 0; i < n; i++) minA[i] = Math.min(nums[i], minA[i - 1])
  for (let i = n - 1; i >= 0; i--) minB[i] = Math.min(nums[i], minB[i + 1])
  // console.log(minA, minB)
  for (let i = 1; i < n - 1; i++) {
    const a = minA[i - 1]; const b = minB[i + 1]
    if (a < nums[i] && b < nums[i]) ans = Math.min(ans, a + nums[i] + b)
  }
  return ans === 1e10 ? -1 : ans
}

```

## 100097. Minimum Number of Groups to Create a Valid Assignment

### 题目

You are given a **0-indexed** integer array `nums` of length `n`.

We want to group the indices so for each index `i` in the range `[0, n - 1]`, it is assigned to **exactly one** group.

A group assignment is **valid** if the following conditions hold:

- For every group `g`, all indices `i` assigned to group `g` have the same value in `nums`.
- For any two groups <code>g<sub>1</sub></code> and <code>g<sub>2</sub></code>, the **difference** between the **number of indices** assigned to <code>g<sub>1</sub></code> and <code>g<sub>2</sub></code> should **not exceed** `1`.

Return _an integer denoting_ _the **minimum** number of groups needed to create a valid group assignment._

**Example 1:**

**Input:** nums = \[3,2,3,2,3\]
**Output:** 2
**Explanation:** One way the indices can be assigned to 2 groups is as follows, where the values in square brackets are indices:
group 1 -> \[0,2,4\]
group 2 -> \[1,3\]
All indices are assigned to one group.
In group 1, nums\[0\] == nums\[2\] == nums\[4\], so all indices have the same value.
In group 2, nums\[1\] == nums\[3\], so all indices have the same value.
The number of indices assigned to group 1 is 3, and the number of indices assigned to group 2 is 2.
Their difference doesn't exceed 1.
It is not possible to use fewer than 2 groups because, in order to use just 1 group, all indices assigned to that group must have the same value.
Hence, the answer is 2.

**Example 2:**

**Input:** nums = \[10,10,10,3,1,1\]
**Output:** 4
**Explanation:** One way the indices can be assigned to 4 groups is as follows, where the values in square brackets are indices:
group 1 -> \[0\]
group 2 -> \[1,2\]
group 3 -> \[3\]
group 4 -> \[4,5\]
The group assignment above satisfies both conditions.
It can be shown that it is not possible to create a valid assignment using fewer than 4 groups.
Hence, the answer is 4.

**Constraints:**

- <code>1 <= nums.length <= 10<sup>5</sup></code>
- <code>1 <= nums[i] <= 10<sup>9</sup></code>

### 算法——贪心

- 根据题意，由于同组的一定是相同数字，答案只和**不同数字的次数**有关，和数字的大小无关。利用哈希表 `cnt[key]=value` 计算出各个数字出现的次数，后面看次数即可。拿到所有 `value` 构成的数组 `a`，从小到大排序。
- 为了使组数尽量少，组中元素应该尽量多，组中元素只能为 `i` 和 `i-1` 两种情况，否则违反第 2 条规则。`i` 最大可取的值只能是 `a[0]+1`，否则 `a[0]` 对应的那些数无法组成一组。遍历 `i` 直到最小可能值 `2`，对于 `a` 中每个次数 `x`，计算 `i` 和 `i-1` 的组合情况，需要满足 `x = m*i+n*(i-1)`，为了使组数最少，`n` 越小越好，可推得 `n=((i-x)%i+i)%i`。
- 虽然是两层循环，但是可以发现两层循环最多把所有的数遍历一遍，因此时间复杂度仍然为 `O(n)`。

### JS 代码

```js
/**
 * @param {number[]} nums
 * @return {number}
 148=1*50+2*49
 x = mi+n(i-1) = (m+n)i-n
 x%i = (-n)%i, 148%50=48=-n+ki
 x%(i-1) = m%(i-1)
 x/i = m+n(i-1)/i
 x/i-1 = mi/(i-1)+n
 */
const minGroupsForValidAssignment = function (nums) {
  const cnt = {}; const n = nums.length
  for (let i = 0; i < n; i++) {
    cnt[nums[i]] ??= 0
    cnt[nums[i]]++
  }
  const a = Object.values(cnt).sort((a, b) => a - b)
  const t = a[0]
  for (let i = t + 1; i >= 2; i--) {
    let ok = true; let g = 0
    for (const x of a) {
      const n = ((i - x) % i + i) % i
      if ((x - n * (i - 1)) % i !== 0 || (x - n * (i - 1)) / i < 0) {
        ok = false
        break
      } else {
        const m = (x - n * (i - 1)) / i
        g += m + n
      }
    }
    if (ok) return g
  }
  return n
}
```

## 6920. Minimum Changes to Make K Semi-palindromes

### 题目

Given a string `s` and an integer `k`, partition `s` into `k` **substrings** such that the sum of the number of letter changes required to turn each **substring** into a **semi-palindrome** is minimized.

Return _an integer denoting the **minimum** number of letter changes required._

**Notes**

- A string is a **palindrome** if it can be read the same way from left to right and right to left.
- A string with a length of `len` is considered a **semi-palindrome** if there exists a positive integer `d` such that `1 <= d < len` and `len % d == 0`, and if we take indices that have the same modulo by `d`, they form a **palindrome**. For example, `"aa"`, `"aba"`, `"adbgad"`, and, `"abab"` are **semi-palindrome** and `"a"`, `"ab"`, and, `"abca"` are not.
- A **substring** is a contiguous sequence of characters within a string.

**Example 1:**

**Input:** s = "abcac", k = 2
**Output:** 1
**Explanation:** We can divide s into substrings "ab" and "cac". The string "cac" is already a semi-palindrome. If we change "ab" to "aa", it becomes a semi-palindrome with d = 1.
It can be shown that there is no way to divide the string "abcac" into two semi-palindrome substrings. Therefore, the answer would be at least 1.

**Example 2:**

**Input:** s = "abcdef", k = 2
**Output:** 2
**Explanation:** We can divide it into substrings "abc" and "def". Each of the substrings "abc" and "def" requires one change to become a semi-palindrome, so we need 2 changes in total to make all substrings semi-palindrome.
It can be shown that we cannot divide the given string into two substrings in a way that it would require less than 2 changes.

**Example 3:**

**Input:** s = "aabbaa", k = 3
**Output:** 0
**Explanation:** We can divide it into substrings "aa", "bb" and "aa".
The strings "aa" and "bb" are already semi-palindromes. Thus, the answer is zero.

**Constraints:**

- `2 <= s.length <= 200`
- `1 <= k <= s.length / 2`
- `s` consists only of lowercase English letters.

### 算法——预处理+记忆化搜索

- 预处理：计算出 `s` 中所有子串的最小修改次数，存储在 `modify` 数组中，`modify[i][j]` 表示 `s[i]` 到 `s[j]` 的子串的的最小修改次数。
- 记忆化搜索：`dfs(i,j)` 表示将 `s[i]` 到 `s[n-1]` 的子串分成 `j+1` 个子字符串的最小修改次数。`dfs(i,j)=min{modify[i][r]+dfs(r+1,j-1)},i<r<n-j*2`，其中 `r` 表示分割点。
- 算法复杂度
    - 时间复杂度：`O(n^3logn)`。预处理有 `O(n^2)` 个子串，平均每个子串有 `O(logn)` 个因子，每个因子需要 `O(n)` 的时间计算，因此总时间复杂度为 `O(n^3logn)`。
    - 空间复杂度：`O(n^2)`。

### JS 代码

```js
/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
const minimumChanges = function (s, k) {
  const n = s.length; const N = 201
  const modify = Array(n).fill(0).map(() => Array(n).fill(0))
  const divisors = []
  for (let i = 1; i < N; i++) {
    for (let j = i * 2; j < N; j += i) {
      if (divisors[j] == undefined) {
        divisors[j] = []
      }
      divisors[j].push(i)
    }
  }

  const getModify = (s) => {
    let ans = 1e10
    for (const d of divisors[s.length]) {
      let cnt = 0
      for (let i = 0; i < d; i++) {
        let t = ''
        for (let j = i; j < s.length; j += d) {
          t += s[j]
        }
        for (let i = 0; i < t.length / 2; i++) {
          if (t[i] != t[t.length - i - 1]) {
            cnt++
          }
        }
      }
      ans = Math.min(ans, cnt)
    }
    return ans
  }
  for (let i = 0; i < n - 1; i++) {
    for (let j = i + 1; j < n; j++) {
      modify[i][j] = getModify(s.slice(i, j + 1))
    }
  }

  const cache = {}
  const dfs = (i, j) => {
    if (cache[`[${i},${j}]`] != undefined) {
      return cache[`[${i},${j}]`]
    }
    if (j === 0) return modify[i][n - 1]
    let ans = 1e10
    for (let r = i + 1; r < n - j * 2; r++) {
      ans = Math.min(ans, modify[i][r] + dfs(r + 1, j - 1))
    }
    return cache[`[${i},${j}]`] = ans
  }
  return dfs(0, k - 1)
}
```
