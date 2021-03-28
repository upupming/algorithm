# LeetCode Contest 234

- [LeetCode Contest 234](#leetcode-contest-234)
    - [5713. 字符串中不同整数的数目](#5713-字符串中不同整数的数目)
        - [算法](#算法)
            - [线性扫描](#线性扫描)
            - [C++ 代码](#c-代码)
        - [时间复杂度](#时间复杂度)
    - [5715. 还原排列的最少操作步数](#5715-还原排列的最少操作步数)
        - [算法](#算法-1)
            - [模拟](#模拟)
            - [C++ 代码](#c-代码-1)
        - [时间复杂度](#时间复杂度-1)
    - [5714. 替换字符串中的括号内容](#5714-替换字符串中的括号内容)
        - [算法](#算法-2)
            - [哈希表](#哈希表)
            - [C++ 代码](#c-代码-2)
        - [时间复杂度](#时间复杂度-2)
    - [5716. 好因子的最大数目](#5716-好因子的最大数目)
        - [算法](#算法-3)
            - [找规律 + 数学](#找规律--数学)
            - [C++ 代码](#c-代码-3)
        - [时间复杂度](#时间复杂度-3)

## 5713. 字符串中不同整数的数目

### 算法

#### 线性扫描

- 线性扫描，用 `flag = true` 表示当前正在累加数字
- 当遇到一个字母且 `flag = true` 的时候，表示数字累加完毕，利用 `calc` 去除前导 `0` 之后，加入到一个 `set` 中存储，并且清空当前暂存数字、将 `flag` 置为 `false`
- 最终结果就是 `set` 的大小

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string calc(string t) {
        string u;
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == '0' && u == "") continue;
            u += t[i];
        }
        if (t.size() && u == "") u = "0";
        return u;
    }
    int numDifferentIntegers(string w) {
        unordered_set<string> s;
        bool flag = false;
        string t;
        for (int i = 0; i < w.length(); i++) {
            if (isdigit(w[i]) && !flag) {
                t += w[i];
                flag = true;
            } else if (isdigit(w[i])) {
                t += w[i];
            } else if (!isdigit(w[i])) {
                if (flag) {
                    s.insert(calc(t));
                    t = "";
                }
                flag = false;
            }
        }
        if (flag) {
            s.insert(calc(t));
            t = "";
        }
        return s.size();
    }
};

```

### 时间复杂度

- 扫描：`O(n)`
    - 去除前导 0：`O(n)`
- 总时间复杂度：`O(n^2)`

## 5715. 还原排列的最少操作步数

### 算法

#### 模拟

- 答案不会超过 `n`，直接按照题目意思模拟即可

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool notOk(vector<int> &perm) {
        for (int i = 0; i < perm.size(); i++) {
            if (perm[i] != i) return true;
        }
        return false;
    }
    int reinitializePermutation(int n) {
        vector<int> perm(n), arr(n);
        for (int i = 0; i < n; i++) perm[i] = i;

        int cnt = 0;
        do {
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0)
                    arr[i] = perm[i / 2];
                else
                    arr[i] = perm[n / 2 + (i - 1) / 2];
            }
            for (int i = 0; i < n; i++) {
                perm[i] = arr[i];
            }
            cnt++;
        } while (notOk(perm));
        return cnt;
    }
};

```

### 时间复杂度

- 构造哈希表：`O(cnt * n)`，其中 `cnt` 为答案大小，因为 `cnt < n`，所以时间复杂度为 `O(n^2)`

## 5714. 替换字符串中的括号内容

### 算法

#### 哈希表

- 先将 `knowledge` 转化为哈希表数据结构
- 和第一题一样，使用 `flag` 表示当前是否正在括号内部，`flag = true` 时累积当前的括号内字符
- 每次遇到括号尾部的时候，查找哈希表进行对应的替换操作

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> m;
        for (auto& p : knowledge) {
            m[p[0]] = p[1];
        }
        string t, cur;
        bool flag = false;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                flag = true;
            else if (s[i] == ')') {
                if (m.count(cur))
                    t += m[cur];
                else
                    t += '?';
                cur = "";
                flag = false;
            } else {
                if (flag)
                    cur += s[i];
                else
                    t += s[i];
            }
        }
        return t;
    }
};

```

### 时间复杂度

- 构造哈希表：`O(knowledge.length)`
- 线性扫描：`O(knowledge.length)`
- 总时间复杂度：`O(10^5)`

## 5716. 好因子的最大数目

### 算法

#### 找规律 + 数学

- 数据范围很大，无法在线性时间内求解
- 经过找规律发现，如果将 `primeFactors` 个质数分为若干个 `p_i`，每个 `p_i` 出现的次数为 `c_i`，那么必须满足 $sum_{i} c_i = p$，使用这种方案，好因子的数目为 $\prod_{i} c_i$
    - 因为好因子中，每个因子 `p_i` 至少选一个，至多全选，选法总数就是 $\prod_{i} c_i$
- 因此，最终的答案和选的质数没有关系，只和每种质数的个数有关，这道题就转化为了 [LeetCode 343. 整数拆分](https://leetcode-cn.com/problems/integer-break/solution/zheng-shu-chai-fen-by-leetcode-solution/)
- 等价于在 $sum_{i} c_i = p$ 的条件下最大化 $\prod_{i} c_i$
- 因此，能选 `3` 就尽量选 `3`，不行就选 `2`，不能有 `1`

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;

int qpow(int a, int b, int p = P) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}

class Solution {
   public:
    int maxNiceDivisors(int p) {
        if (p == 1) return 1;
        if (p == 2) return 2;
        int q = p / 3, r = p % 3;
        if (r == 0)
            return qpow(3, q);
        else if (r == 1)
            return qpow(3, q - 1) * 4ll % P;
        else
            return qpow(3, q) * 2ll % P;
    }
};

```

### 时间复杂度

- 直接计算：`O(1)`
