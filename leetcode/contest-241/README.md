# LeetCode Contest 241

## 5759. Sum of All Subset XOR Totals

### 算法 —— 二进制枚举模拟

- 用一个数 `i` 表示一个集合，数 `i` 的第 `j` 位表示第 `j` 个数是否属于当前枚举的集合
- 对所有集合的 XOR 值作和

### 时间复杂度

- 枚举: `O(2^n)`
    - 计算和: `O(n)`
- 总时间复杂度: `O(n * 2^n)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 1; i < 1 << n; i++) {
            int x = 0;
            for (int j =0; j < n; j++) {
                if (i >>j & 1) {
                    x ^= nums[j];
                }
            }
            ans += x;
        }
        return ans;
    }
};
```

## 5760. Minimum Number of Swaps to Make the Binary String Alternating

### 算法 —— 分类讨论

- `0` 和 `1` 的个数之差必须为 `<=1`，不然无法排成题目要求的格式
- 最终的格式只能有两种 `0101...` 或者 `1010...`
- 分别计算这两种格式和原始字符串的最小交换次数即可，由于可以任意交换两个下标，交换次数就是相同下标不同数的个数

### 时间复杂度

- 构造 & 求交换次数: `O(n)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int cntNum(string &s, int x) {
        int ans = 0;
        for (auto ch : s) {
            if (ch - '0' == x) ans++;
        }
        return ans;
    }
    int cntSwap(string &s, string &t) {
        int n = s.length();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                ans++;
            }
        }
        return ans / 2;
    }
    int minSwaps(string s) {
        int n = s.length();
        int c0 = cntNum(s, 0), c1 = cntNum(s, 1);
        if (abs(c0 - c1) >= 2) return -1;
        string s0, s1;
        for (int i = 0; i < c0 && i < c1; i++) {
            s0 += "01";
            s1 += "10";
        }
        for (int i = min(c0, c1); i < c0; i++) {
            s0 += "0";
        }
        for (int i = min(c0, c1); i < c1; i++) {
            s1 += "1";
        }
        int ans = INT_MAX;
        if (s0.length() == n) ans = min(ans, cntSwap(s, s0));
        if (s1.length() == n) ans = min(ans, cntSwap(s, s1));
        return ans;
    }
};

```

## 5761. Finding Pairs With a Certain Sum

### 算法 —— map 查询

- 注意到 `nums1` 的数的个数比较小，因此查询 `tot` 的时候，可以枚举 `nums1` 里面所有的数 `a`，在 `nums2` 里面查询 `tot-a` 的个数
- 初始化的时候需要同时初始化 `map` 用来存储 `nums2` 里面每个数的个数
- 更新的时候同步维护 `map`

### 时间复杂度

- 构造: `O(nums2.length)`
- 添加: `O(1)`
- 统计: `O(nums1.length)`

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class FindSumPairs {
   public:
    vector<int> nums1, nums2;
    unordered_map<int, int> cnt2;
    FindSumPairs(vector<int>& _nums1, vector<int>& _nums2) {
        nums1 = _nums1, nums2 = _nums2;
        for (auto& a : nums2) {
            cnt2[a]++;
        }
    }

    void add(int index, int val) {
        int old = nums2[index];
        nums2[index] += val;
        cnt2[old]--, cnt2[nums2[index]]++;
    }

    int count(int tot) {
        int ans = 0;
        for (auto& a : nums1) {
            int val = tot - a;
            if (cnt2.count(val)) ans += cnt2[val];
        }
        return ans;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */

```

## 5762. Number of Ways to Rearrange Sticks With K Sticks Visible

### 算法 —— 动态规划

- 想到了 DP，但是状态转移不太会（前面的数的顺序有点懵），直接猜的，居然蒙对了，下来才知道是斯特林数（之前没学过）
-
    - 如果将 `i` 放在最后，那么剩下的 `i-1` 个数一定有 `j-1` 个 visible 的，也就是 `f[i-1][j]`
    - 否则，我们枚举 `i` 放在前面的某个地方，我就是在这里卡住了
- 最后的答案就是 `f[n][k]`

---

- （第一类）斯特林数 `f[i][j]` 的定义是「将 i 个不同元素构成 j 个圆排列的数目」
- n 个数的圆排列个数是 (n-1)!（固定第 1 个数，其他数任意排列）
- 这个题目和斯特林数是一样的，用 `f[i][j]` 表示 `1~i` 组成的数组，有 `j` 个 visible 的数的方案个数
    - 其实 `f[i][j]` 就是斯特林数，因为 `j` 个 visible，那么可以将 `i` 个数分成 `j` 个递减的部分，每个部分都是最高的在最前面固定住，其他元素任意排列，有 `(j-1)!` 种方案
    - 转移过程:
        - 如果第 `i` 个数自己一个人组成一组，那么剩下的就是 `f[i-1][j-1]`
        - 如果第 `i` 个数和其他组一组，那么就是 `f[i-1][j] * (i-1)`，因为第 `i` 可以放在 `(i-1)` 个组中的任意一个组，由于最高必须放在其第 1 个位置（1 种方法）。

### 时间复杂度

- O(n^2)

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1010, P = 1e9 + 7;
LL f[N][N];
class Solution {
   public:
    int rearrangeSticks(int n, int k) {
        memset(f, 0, sizeof f);
        f[1][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                f[i][k] += (f[i - 1][k - 1] + f[i - 1][k] * (i - 1)) % P;
            }
        }
        return f[n][k];
    }
};

```
