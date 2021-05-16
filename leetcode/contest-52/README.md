# LeetCode Contest 52

## 5742. 将句子排序

### 算法 —— split + join

- 先将字符串 `split` 成数组
- 按照末尾数字排序，去除末尾数字
- 重新 `join` 成字符串
- C++ 没有 `split` 和 `join` 需要手写，因此我直接写 TypeScript

### 时间复杂度

- 遍历字符串进行 `split`+`join`: `O(n)`

### TypeScript 代码

```ts
function sortSentence (s: string): string {
  const a = s.split(' '); const b = []
  for (const t of a) {
    b[t[t.length - 1].charCodeAt(0) - '1'.charCodeAt(0)] = t.substr(0, t.length - 1)
  }
  return b.join(' ')
};

```

## 5743. 增长的内存泄露

### 算法 —— 最大堆

- 用最大堆存储当前的两个内存空间，由于第 1 个内存条更优先，用 `pair` 的第二个字段用来在内存剩余相等的时候排序两个内存条
- 不断迭代知道堆顶空间不足时刻 `i` 的需求，返回答案即可

### 时间复杂度

- 假设出堆 `n` 次，时间复杂度为 `O(n)`，则有 `1+2+...+n=O(2^31)`

### C++ 代码

```c++
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<int> memLeak(int memory1, int memory2) {
        priority_queue<pair<int, int>> q;
        q.push({memory1, 1}), q.push({memory2, 0});
        for (int i = 1;; i++) {
            if (q.top().first < i) {
                int a[2];
                while (q.size()) {
                    auto now = q.top();
                    a[now.second] = now.first;
                    q.pop();
                }
                return {i, a[1], a[0]};
            }
            auto now = q.top();
            now.first -= i;
            q.pop();
            q.push(now);
        }
        return {-1, -1, -1};
    }
};

```

## 5744. 旋转盒子

### 算法 —— 模拟

- 顺时针旋转 `box'[i][j] = box[m - 1 - j][i]`，因为 `box'` 的第 `i` 行是 `box` 的第 `i` 列，`box'` 的第 `j` 列是 `box` 的第 `m-1-j` 行
- 之后至下往上模拟，每次遇到一个石头，不断进行下落（通过 `swap` 实现）直到遇到障碍物或者触底。

### 时间复杂度

- `O(n^2 * m)`: 理论上比较大，但是实际上很难达到这个复杂度，所以可以过

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size(), n = box[0].size();
        vector<vector<char>> ans(n, vector<char>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][j] = box[m - 1 - j][i];
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                if (ans[i][j] != '#') continue;
                int k = i + 1;
                while (k < n && ans[k][j] == '.') {
                    swap(ans[k][j], ans[k - 1][j]);
                    k++;
                }
            }
        }
        return ans;
    }
};

```

## 5212. 向下取整数对和

### 算法 —— 二分

- 将原数组排序
- 从小到大枚举每一个数 `nums[i]`，枚举 `x/nums[i]=j` 的所有 `j`，二分查找 `x` 在 `nums` 中可能出现的位置，统计长度即可

### 时间复杂度

- `O(n * sum(t_i)) < O(n^2)`: 其中 `t_i` 表示 `nums[i]` 枚举的 `j` 的数量，等于 `max(nums)/nums[i]`，实际上很难达到 `O(n^2)`，所以可以过
    - 开始 TLE 了，加一个优化，当前数和前一个数相等时，直接使用上次计算过的值。

### C++ 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
typedef long long LL;
class Solution {
   public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        nums.insert(nums.begin(), -1);
        nums.push_back(INT_MAX);

        LL ans = 0, last = -1;
        for (int i = 1; i <= n; i++) {
            if (nums[i] == nums[i - 1]) {
                ans = (ans + last) % P;
                continue;
            }
            last = 0;
            LL a = nums[i];
            // j 的次数: ?/a=j
            for (int j = 0;; j++) {
                LL x = (j + 1ll) * a;
                // 找到 < x 的最右边
                int l = 0, r = n + 1;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (nums[mid] < x)
                        l = mid;
                    else
                        r = mid - 1;
                }
                int tmp = l;
                // >=y 的最左边
                LL y = (LL)j * a;
                l = 0, r = n + 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (nums[mid] >= y)
                        r = mid;
                    else
                        l = mid + 1;
                }
                if (l == n + 1) break;
                if (tmp >= l) {
                    ans = (ans + (tmp - l + 1ll) * j) % P;
                    last += (tmp - l + 1ll) * j;
                }
            }
        }
        return ans;
    }
};

```
