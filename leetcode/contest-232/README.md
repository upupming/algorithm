# LeetCode Contest 232 题解

- [LeetCode Contest 232 题解](#leetcode-contest-232-题解)
  - [5701. 仅执行一次字符串交换能否使两个字符串相等](#5701-仅执行一次字符串交换能否使两个字符串相等)
    - [算法](#算法)
      - [暴力枚举 $O(n^2)$](#暴力枚举-on2)
      - [C++ 代码](#c-代码)
  - [5702. 找出星型图的中心节点](#5702-找出星型图的中心节点)
    - [算法](#算法-1)
      - [暴力枚举 $O(n)$](#暴力枚举-on)
      - [C++ 代码](#c-代码-1)
  - [5703. 最大平均通过率](#5703-最大平均通过率)
    - [算法](#算法-2)
      - [贪心、优先队列 $O(n log n)$](#贪心优先队列-on-log-n)
      - [C++ 代码](#c-代码-2)
  - [5704. 好子数组的最大分数](#5704-好子数组的最大分数)
    - [算法](#算法-3)
      - [单调栈 + 双指针 $O(n)$](#单调栈--双指针-on)
      - [C++ 代码](#c-代码-3)
      - [类似题目](#类似题目)

> 这次题目比较中规中矩，小菜鸡人生中第一次 AK LeetCode Contest，值得庆祝 :)

## 5701. 仅执行一次字符串交换能否使两个字符串相等

### 算法

#### 暴力枚举 $O(n^2)$

- 特判一下两个字符串是否相等，如果相等，直接返回 `true`
- 枚举 `s1` 可能交换的下标 `i` 和 `j`，交换之后如果和 `s2` 相等，返回 `true`
- 其他情况，均返回 `false`

#### C++ 代码

```cpp
class Solution {
   public:
    bool areAlmostEqual(string s1, string s2) {
        if (s1 == s2) return true;
        int n = s1.length();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto t = s1;
                swap(t[i], t[j]);
                if (t == s2) return true;
            }
        }
        return false;
    }
};
```

## 5702. 找出星型图的中心节点

### 算法

#### 暴力枚举 $O(n)$

- 遍历所有的边，累加每个顶点的度
- 返回度最大的节点即可

#### C++ 代码

```cpp
class Solution {
   public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, int> deg;
        int maxDeg = 0, ans;
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            deg[x]++, deg[y]++;
            if (deg[x] > maxDeg) {
                maxDeg = deg[x];
                ans = x;
            }
            if (deg[y] > maxDeg) {
                maxDeg = deg[y];
                ans = y;
            }
        }
        return ans;
    }
};
```

## 5703. 最大平均通过率

### 算法

#### 贪心、优先队列 $O(n log n)$

- 枚举所有的聪明学生，每次插入到对平均通过率增加贡献最大的那一个班级中，最后对所有班级求一个平均通过率
- 对【平均通过率】增加贡献最大，等价于对【自己班级】增加贡献最大
- 假设某班级的通过比为 $\frac{a}{b}$，增加一个聪明学生之后通过比为 $\frac{a+1}{b+1}$，增加量为 $\frac{a+1}{b+1} - \frac{a}{b} = \frac{b-a}{b(b+1)}$
- 因此，自定义优先队列的排序方式为，按照每个班级的 $\frac{b-a}{b(b+1)}$ 值从大到小排列，每次取出值最大的班级增加一个优秀学生，之后再次放入堆中

#### C++ 代码

```cpp
class Solution {
    struct P {
        int a, b;
        double g;
        double calc() const {
            return double(b - a) / b / (b + 1);
        }
        bool operator<(const P& x) const {
            return calc() < x.calc();
        }
    };

   public:
    double maxAverageRatio(vector<vector<int>>& cls, int e) {
        priority_queue<P> pq;
        for (auto& c : cls) {
            P p;
            p.a = c[0], p.b = c[1], p.g = (double)p.a / p.b;
            pq.push(p);
        }
        while (e--) {
            auto q = pq.top();
            pq.pop();
            q.a++, q.b++, q.g = (double)q.a / q.b;
            pq.push(q);
        }
        double ans = 0;
        while (pq.size()) {
            auto q = pq.top();
            pq.pop();
            ans += q.g;
        }
        return ans / cls.size();
    }
};
```

## 5704. 好子数组的最大分数

### 算法

#### 单调栈 + 双指针 $O(n)$

- 让 `i` 和 `j` 均从 `k` 开始向两边进行扩展，每次计算当前分数，如果大于当前 `ans`，则更新 `ans`。
- 如果当前时刻 `nums[i-1] > nums[j+1]`，显然是让 `i` 向左边扩展一个下标最优。不然的话，`j` 向右扩展一个下标，总能让 `i` 向左边也扩展一步，而保持区间 min 值不变，长度增加，结果增加。反之 `nums[i-1] < nums[j+1]` 亦然。
- 关键问题在于 `nums[i-1] == nums[j+1]` 时的处理，这个时候要比较 `nums[i-1]` 左侧第一个不同于 `nums[i-1]` 的数和 `nums[j+1]` 右侧第一个不同于 `nums[j+1]` 的数。
- 因此，我们需要用单调栈预处理数组 `s` 和 `t`。
  - `s[i]` 表示 `nums[i]` 左侧第一个不同于 `nums[i]` 的数
  - `t[i]` 表示 `nums[i]` 右侧第一个不同于 `nums[i]` 的数

#### C++ 代码

```cpp
class Solution {
   public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = nums[k];
        vector<int> s(n), t(n);
        s[0] = t[n - 1] = -1;
        stack<int> stk;
        stk.push(nums[0]);
        for (int i = 1; i < n; i++) {
            if (stk.size() && stk.top() == nums[i]) {
                stk.pop();
            }
            if (!stk.size())
                s[i] = -1;
            else
                s[i] = stk.top();
            stk.push(nums[i]);
        }
        stack<int> stk2;
        stk.push(nums[n - 1]);
        for (int i = n - 2; i >= 0; i--) {
            if (stk2.size() && stk2.top() == nums[i]) {
                stk2.pop();
            }
            if (!stk2.size())
                t[i] = -1;
            else
                t[i] = stk2.top();
            stk2.push(nums[i]);
        }

        for (int i = k, j = k, m = nums[k]; i >= 0 && j < n;) {
            ans = max(ans, m * (j - i + 1));
            if (i == 0 && j == n - 1) {
                break;
            }
            if (i == 0) {
                m = min(m, nums[++j]);
            } else if (j == n - 1) {
                m = min(m, nums[--i]);
            } else {
                if (nums[i - 1] == nums[j + 1]) {
                    if (s[i - 1] > t[j + 1]) {
                        m = min(m, nums[--i]);
                    } else {
                        m = min(m, nums[++j]);
                    }
                } else if (nums[i - 1] > nums[j + 1]) {
                    m = min(m, nums[--i]);
                } else {
                    m = min(m, nums[++j]);
                }
            }
        }

        return ans;
    }
};
```

#### 类似题目

1. [https://leetcode-cn.com/problems/largest-merge-of-two-strings/](https://leetcode-cn.com/problems/largest-merge-of-two-strings/)
   - 这里相等的时候的处理，和这道题目非常类似

> 最后试了一下，相等的时候，随便扩展就行，因为我们总会拓展到另一侧，所以不影响

```cpp
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = nums[k];
        for (int i = k, j = k, m = nums[k]; i >= 0 && j < n;) {
            ans = max(ans, m * (j - i + 1));
            if (i == 0 && j == n-1) {
                break;
            }
            if (i == 0) {
                m = min(m, nums[++j]);
            }
            else if (j == n-1) {
                m = min(m, nums[--i]);
            } else {
                 if (nums[i-1] > nums[j+1]) {
                    m = min(m, nums[--i]);
                } else {
                    m = min(m, nums[++j]);
                }
            }
        }

        return ans;
    }
};
```
