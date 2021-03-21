# LeetCode Contest 233 题解

- [LeetCode Contest 233 题解](#leetcode-contest-233-题解)
  - [5709. 最大升序子数组和](#5709-最大升序子数组和)
    - [算法](#算法)
      - [暴力枚举 $O(n^2)$](#暴力枚举-on2)
      - [C++ 代码](#c-代码)
  - [5710. 积压订单中的订单总数](#5710-积压订单中的订单总数)
    - [算法](#算法-1)
      - [最大堆+最小堆 $O(n log n)$](#最大堆最小堆-on-log-n)
      - [C++ 代码](#c-代码-1)
  - [5711. 有界数组中指定下标处的最大值](#5711-有界数组中指定下标处的最大值)
    - [算法](#算法-2)
      - [二分 $O(log maxSum)$](#二分-olog-maxsum)
      - [C++ 代码](#c-代码-2)
  - [5696. 统计异或值在范围内的数对有多少](#5696-统计异或值在范围内的数对有多少)
    - [算法](#算法-3)
      - [Trie + dfs $O(n^2)$](#trie--dfs-on2)
      - [C++ 代码](#c-代码-3)

## 5709. 最大升序子数组和

### 算法

#### 暴力枚举 $O(n^2)$

- 枚举区间起点 `i`，计算区间内从 `i` 开始最长的上升子数组的终点 `j`，并求和
- 用最大的和更新答案

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int maxAscendingSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int sum = nums[i];
            for (int j = i + 1; j < n; j++) {
                if (nums[j] > nums[j - 1]) {
                    sum += nums[j];
                } else {
                    break;
                }
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};

```

## 5710. 积压订单中的订单总数

### 算法

#### 最大堆+最小堆 $O(n log n)$

- 按照题目意思模拟即可
- 每次遇到 `buy` 都需要找到最低的 `sell`，因此 `sell` 用最小堆存储，使用 `pair`，第一个关键字是订单价格用来排序，第二个关键之是订单数量
- 同理，`buy` 用最大堆存储
- 每次遇到新的 `buy` 订单，去 `sell` 中执行对应的更新操作；反之同理。
- 最后，两个堆中剩余的订单总数就是答案

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int P = 1e9 + 7;
class Solution {
   public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        priority_queue<PII> buy;
        priority_queue<PII, vector<PII>, greater<PII>> sell;
        for (auto& o : orders) {
            // buy
            if (o[2] == 0) {
                while (o[1] && sell.size() && sell.top().first <= o[0]) {
                    if (sell.top().second <= o[1]) {
                        o[1] -= sell.top().second;
                        sell.pop();
                    } else {
                        auto now = sell.top();
                        sell.pop();
                        now.second -= o[1];
                        sell.push(now);
                        o[1] = 0;
                    }
                }
                if (o[1]) {
                    buy.push({o[0], o[1]});
                }
            } else {
                // sell
                while (o[1] && buy.size() && buy.top().first >= o[0]) {
                    if (buy.top().second <= o[1]) {
                        o[1] -= buy.top().second;
                        buy.pop();
                    } else {
                        auto now = buy.top();
                        buy.pop();
                        now.second -= o[1];
                        buy.push(now);
                        o[1] = 0;
                    }
                }
                if (o[1]) {
                    sell.push({o[0], o[1]});
                }
            }
            // cout << buy.size() << " " << sell.size() << endl;
        }
        int ans = 0;
        while (sell.size()) {
            ans = (ans + sell.top().second) % P;
            sell.pop();
        }
        while (buy.size()) {
            ans = (ans + buy.top().second) % P;
            buy.pop();
        }
        return ans;
    }
};

```

## 5711. 有界数组中指定下标处的最大值

### 算法

#### 二分 $O(log maxSum)$

- `n = 1e9` 数据范围比较大，再加上要求的是一个数值，可以直接二分，转化为判定问题，每次判断将 `nums[index] = k` 是否满足。下面是判定过程：
- 考虑 `0~(index-1)` 的范围的赋值情况，一共有 `index` 个数，我们要尽量给每个数分配较小的值，使得尽量不超过 `maxSum`。我们最小可以分配到 `[1, 2, ..., k - 1]` 共 `k-1` 个数，如果 `k-1 >= index`，那么我们分配的数是 `[k-1-(index-1), ..., k-1]` （公差为 1 的等差数列），否则的话，我们分配的数是 `[1, 1, ..., 1, 2, ..., k-1]`，其中后 `k-1` 个数构成等差数列，左侧剩下 `index-(k-1)` 个 1。
- 接着考虑 `(index+1)~(n-1)` 的范围的赋值情况，实际上可以等价于把数组反转，考虑从 `0~(n-1-index)` 的情况。因此，单独将上述计算过程抽成函数，用不同参数计算两遍。
- 最后加上 `nums[index]`，判断和是否不超过 `maxSum`。

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Solution {
    int n, idx, mS;
    LL calc(int mid, int idx) {
        LL sum = 0;
        if (mid - idx >= 1) {
            int left = mid - idx;
            sum += (left + mid - 1ll) * idx / 2;
        } else {
            sum += (1ll + mid - 1) * (mid - 1) / 2;
            sum += (idx + 1ll - mid) * 1;
        }
        return sum;
    }
    bool valid(int mid) {
        LL sum = calc(mid, idx) + calc(mid, n - 1 - idx) + mid;
        // cout << mid << " " << calc(mid) << " " << calc(n - 1 - idx) << " " << mid << " " << sum << endl;
        if (sum <= mS) return true;
        return false;
    }

   public:
    int maxValue(int _n, int index, int maxSum) {
        n = _n, idx = index, mS = maxSum;
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (valid(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }
};

```

## 5696. 统计异或值在范围内的数对有多少

### 算法

#### Trie + dfs $O(n^2)$

- 转化为求解：异或和在 `[0, high]` 的数的对数，减去，异或和在 `[0, low-1]` 的数的对数，即 `solve(high) - solve(low-1)`。
- 先将所有数插入到 trie 树中
- 利用 dfs 计算一个数 x 能和多少对数（`cnt[x]`）组成 `> k`，`solve(k)` 的答案就是 `n * (n - 1) / 2 - sum_{所有可能的 x}(cnt[x]) / 2`，即总对数减去不满足 `<=` 的对数。
- `dfs` 从高位到低位逐渐进行，当发现后续即使所有位都置为 1，也无法达到 `> k` 时，可以提前剪枝。
- 相关题目：AcWing 143

#### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace std;
const int N = 15 * 2 * 1e4 + 10;
int trie[N][2], n, a, tot = 1, p, cnt[N];
class Solution {
    vector<int> nums;
    int n;
    // 计算有多少数和 x 异或之后 > maxXor
    int dfs(int x, int p, int q, int curXor, int k, int maxXor) {
        if (k == -1) return 0;
        int j = x >> k & 1;
        p = trie[p][j];
        int ans = 0;
        // 寻找匹配，能够匹配一个不同的位的话
        if (trie[q][!j]) {
            int newXor = curXor | 1 << k;
            int newQ = trie[q][!j];
            if (newXor > maxXor)
                ans += cnt[newQ];
            // 后续即使全部为 1 也无法达到 maxXor，提前剪枝
            else if (newXor + (1 << k) - 1 > maxXor) {
                ans += dfs(x, p, newQ, newXor, k - 1, maxXor);
            }
        }
        // 后续即使全部为 1 也无法达到 maxXor，提前剪枝
        if (curXor + (1 << k) - 1 > maxXor) {
            // 匹配一个相同的位
            int newQ = trie[q][j];
            ans += dfs(x, p, newQ, curXor, k - 1, maxXor);
        }
        return ans;
    }
    // 有多少对的异或值在 [0, maxXor] 之间
    int solve(int maxXor) {
        int ans = 0;
        for (auto& a : nums) {
            ans += dfs(a, 1, 1, 0, 15, maxXor);
        }
        // cout << maxXor << ", " << ans << "," << (n * (n - 1) / 2 - ans / 2) << endl;
        return n * (n - 1) / 2 - ans / 2;
    }

   public:
    int countPairs(vector<int>& _nums, int low, int high) {
        nums = _nums, n = nums.size();
        memset(trie, 0, sizeof trie);
        memset(cnt, 0, sizeof cnt);
        int ans = 0;
        tot = 1;
        for (auto& a : nums) {
            p = 1, cnt[p]++;
            for (int i = 15; i >= 0; i--) {
                int j = a >> i & 1;
                if (trie[p][j] == 0) trie[p][j] = ++tot;
                p = trie[p][j];
                cnt[p]++;
            }
        }

        return solve(high) - solve(low - 1);
    }
};

```
