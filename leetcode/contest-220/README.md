# LeetCode Contest 220 题解

- [LeetCode Contest 220 题解](#leetcode-contest-220-题解)
  - [5629. Reformat Phone Number](#5629-reformat-phone-number)
    - [算法](#算法)
    - [时间复杂度](#时间复杂度)
    - [C++ 代码](#c-代码)
  - [5630. Maximum Erasure Value](#5630-maximum-erasure-value)
    - [算法](#算法-1)
    - [时间复杂度](#时间复杂度-1)
    - [C++ 代码](#c-代码-1)
  - [5631. Jump Game VI](#5631-jump-game-vi)
    - [算法](#算法-2)
    - [时间复杂度](#时间复杂度-2)
  - [5632. Checking Existence of Edge Length Limited Paths](#5632-checking-existence-of-edge-length-limited-paths)
    - [算法](#算法-3)
    - [时间复杂度](#时间复杂度-3)
    - [C++ 代码](#c-代码-2)

## 5629. Reformat Phone Number

https://leetcode.com/contest/weekly-contest-220/problems/reformat-phone-number/

### 算法

字符串处理。

两趟扫描，第一趟删去空格和 `-`，第二趟计算组数和多余的串，然后进行拼接。注意一下边界问题。

### 时间复杂度

$O(N)$

### C++ 代码

```cpp
class Solution {
   public:
    string reformatNumber(string number) {
        int n = number.length();
        string t, ans;
        for (int i = 0; i < n; i++) {
            if (number[i] == '-' || number[i] == ' ') continue;
            t += number[i];
        }
        int m = t.length(), g = m / 3, r = m % 3;
        if (r == 1) g--, r += 3;
        for (int i = 0; i < g; i++) {
            if (i > 0)
                ans += '-';
            ans += t.substr(3 * i, 3);
        }
        if (r == 2)
            ans += (g > 0 ? "-" : "") + t.substr(m - r, 2);
        else if (r == 4)
            ans += (g > 0 ? "-" : "") + t.substr(m - 4, 2) + '-' + t.substr(m - 2, 2);
        return ans;
    }
};
```

## 5630. Maximum Erasure Value

https://leetcode.com/contest/weekly-contest-220/problems/maximum-erasure-value/

### 算法

- 双指针 `l` 和 `r` 分别指向区间起点和终点。
- 每次 `r` 增加 $1$，判断一下 `l` 右侧是否有和 `nums[r]` 相同的数，如果下标为 `i`，则将 `l` 更新为 `i+1`。
- 每次 `l`、`r` 更新，如果区间和大于当前答案，就更新一下答案，区间和可以通过前缀和在 $O(1)$ 时间内计算得到。

### 时间复杂度

- 前缀和：$O(N)$
- 双指针扫描枚举：$O(N)$
- `map` 查询是否存在：$O(N \log N)$
- 总时间复杂度为：$O(N \log N)$

### C++ 代码

```cpp
class Solution {
   public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];

        map<int, int> mp;
        int l = 0, r = 0;
        int ans = nums[0];

        while (r < n) {
            if (mp.count(nums[r])) {
                int i = mp[nums[r]];
                l = max(l, i + 1);
            }
            ans = max(ans, sum[r + 1] - sum[l]);
            mp[nums[r]] = r;
            r++;
        }
        return ans;
    }
};
```

## 5631. Jump Game VI

https://leetcode.com/contest/weekly-contest-220/problems/jump-game-vi/

### 算法

- 动态规划。用 `dp[i]` 表示以 `i` 为结尾的最大 score。初始状态 `dp[0] = nums[0]`，转移方程 $dp(j) = \max_{i = j-k, ..., j-1}{dp(i) + nums[j]}$，最终结果就是 `dp[n-1]`。
- 为了方便计算 `[j-k, j-1]` 区间内的 `dp` 最大值，可以维护一个单调队列，每次入队列时删去队尾较小的值（因为越远，值越小的元素总能被越近、值越大的元素替代）。
    - 滑动窗口极值经典题 [AcWing 154. 滑动窗口](https://www.acwing.com/problem/content/description/156/)，[参考题解](https://www.acwing.com/file_system/file/content/whole/index/content/1537529/)
- 队列满足单调递减，队头永远都是最大值。注意每次取队头来进行转移的时候，先删去超出距离 `k` 的元素

### 时间复杂度

- 动态规划：$O(N)$
- 单调队列：$O(N)$
- 总时间复杂度：$O(N)$

```cpp
class Solution {
   public:
    int maxResult(vector<int>& w, int k) {
        int n = w.size();
        vector<int> dp(n + 1, 0);
        deque<int> dqMax;
        dp[0] = w[0];
        dqMax.push_back(0);
        for (int i = 1; i < n; i++) {
            while (dqMax.size() && i - dqMax.front() > k) {
                dqMax.pop_front();
            }

            int maxIdx = dqMax.front();
            dp[i] = dp[maxIdx] + w[i];

            while (dqMax.size() && dp[dqMax.back()] <= dp[i]) {
                dqMax.pop_back();
            }

            dqMax.push_back(i);
        }
        return dp[n - 1];
    }
};
```

## 5632. Checking Existence of Edge Length Limited Paths

https://leetcode.com/contest/weekly-contest-220/problems/checking-existence-of-edge-length-limited-paths/

之前没见过这题，参考了 [y 总的题解](https://www.acwing.com/activity/content/code/content/647839/)，y 总 NB。

### 算法

- 并查集。给定 `dis` 限制的条件下，只把边权小于 `dis` 的边算入，然后用并查集判断 `u` 和 `v` 之间是否连通即可。
- 边排序、查询排序、每个边只加入一次。如果查询按照 `dis` 增加的顺序进行，那么我们可以依次加入权值小于 `dis` 边，而不用删除上次查询已经加入的边。因此每个边只需要加入一次。

### 时间复杂度

- 预处理：$O(M+K)$，$M$ 为边的条数，$K$ 为查询次数
- 排序：$O((M+K) \log (M+K))$
- 并查集：预处理 $O(N)$，所有查询操作 $O((M+K) \log N)$
- 总时间复杂度：$O(N) + O((M+K) (\log (M+K) + \log N))$

### C++ 代码

```cpp
const int N = 1e5 + 10;
struct Node {
    int u, v, dis, idx;
    bool operator<(const Node& b) {
        return dis < b.dis;
    }
} e[N], q[N];

class Solution {
    vector<int> parent;
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

   public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int m = edgeList.size(), k = queries.size();
        for (int i = 0; i < m; i++)
            e[i] = {edgeList[i][0], edgeList[i][1], edgeList[i][2]};
        for (int i = 0; i < k; i++)
            q[i] = {queries[i][0], queries[i][1], queries[i][2], i};

        sort(e, e + m);
        sort(q, q + k);

        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        vector<bool> ans(k);
        // 类似双指针，右端点 i 表示查询，左端点 j 表示边
        for (int i = 0, j = 0; i < k; i++) {
            while (j < m && e[j].dis < q[i].dis) {
                int x = find(e[j].u);
                parent[x] = find(e[j].v);
                j++;
            }
            ans[q[i].idx] = (find(q[i].u) == find(q[i].v));
        }

        return ans;
    }
};
```
