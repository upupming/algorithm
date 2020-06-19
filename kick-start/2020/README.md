# Google Kickstart 2020

- [Google Kickstart 2020](#google-kickstart-2020)
  - [Round A](#round-a)
    - [A. Allocation](#a-allocation)
      - [题目大意](#题目大意)
      - [解析](#解析)
      - [代码](#代码)
    - [B. Plates](#b-plates)
      - [题目大意](#题目大意-1)
      - [解析](#解析-1)
      - [代码](#代码-1)
    - [C. Workout](#c-workout)
      - [题目大意](#题目大意-2)
      - [解析 1](#解析-1)
      - [代码 1](#代码-1)
      - [解析 2](#解析-2)
      - [代码 2](#代码-2)
    - [D. Bundling](#d-bundling)
      - [题目大意](#题目大意-3)
      - [解析](#解析-2)
      - [代码](#代码-2)

## Round A

### A. Allocation

#### 题目大意

总共 N 个房子，价格不同，求 B 美元最多可以买多少房子。

#### 解析

将所有房子价格排序，然后求前缀和，前缀和大于 B 的地方前面所有房子就是 B 这么多钱能够购买的最多的房子总数。

#### 代码

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

int t, n, a[100005], b;

int solve() {
    sort(a, a + n);
    int i = 0;
    for (; i < n; i++) {
        if (i != 0) {
            a[i] = a[i - 1] + a[i];
        }
        if (a[i] > b) break;
    }
    return i;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> b;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

### B. Plates

#### 题目大意

现有 N 叠盘子，每叠有 K 个盘子，每个盘子一个价值，要从这 N 叠盘子中取 P 个盘子，最大化价值总和。限制是要取出一个盘子，这个盘子之上的所有盘子都要取出来。

#### 解析

因为要取一个盘子，就需要取出这个盘子之上的所有盘子，我们同样先求出前缀和，用来表示取出一个盘子及其上面所有盘子取得的总价值。

使用深度优先搜索，第 i 叠盘子选择 $k_i$ 个盘子，对后续所有情况得到的价值取最大值。可以加入缓存对 dfs 运行结果进行存储。

#### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int t, n, k, p, v[55][35];
// 缓存 dfs 结果
map<int, map<int, int>> m;

int dfs(int stack_no, int p) {
    if (m.count(stack_no) && m[stack_no].count(p)) {
        return m[stack_no][p];
    }

    if (p == 0) return 0;
    if (stack_no == n - 1) return v[stack_no][min(p - 1, k - 1)];

    int res = 0;
    // i 表示第 stack_no 叠盘子选择的盘子总数
    for (int i = 0; i <= min(p, k); i++) {
        // value 表示此次选择带来的收益价值
        int value = 0;
        if (i != 0) {
            value = v[stack_no][i - 1];
        }

        res = max(res, dfs(stack_no + 1, p - i) + value);
    }

    m[stack_no][p] = res;
    return res;
}

int solve() {
    // Prefix sum calculation
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < k; b++) {
            if (b != 0) {
                v[a][b] = v[a][b - 1] + v[a][b];
            }
        }
    }
    // DFS
    return dfs(0, p);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        m.clear();
        cin >> n >> k >> p;
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < k; b++) {
                cin >> v[a][b];
            }
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

### C. Workout

#### 题目大意

N 次锻炼，第 i 次锻炼时间为 $M_i$，时间单调递增，定义最大的相邻时间差为锻炼难度，在 N 次锻炼中插入 K 次新的锻炼（保持单调递增），使得难度尽量小，求最小的难度值。

#### 解析 1

> 这种方法时间复杂度比较高，最终在 Test set 2 TLE 了。

以 9 10 20 26 30 为例，时间差分别为 1, 10, 6, 4，排序之后为 10, 6, 4, 1，将其组织成一个最大堆，每次取出堆顶的元素将其一分为二。一共六次机会，依次操作如下：

1. 6, 5, 5, 4, 1
2. 5, 5, 4, 3, 3, 1
3. 5, 4, 3, 3, 3, 2, 1
4. 4, 3, 3, 3, 3, 2, 2, 1
5. 3, 3, 3, 3, 2, 2, 2, 2, 1
6. 3, 3, 3, 2, 2, 2, 2, 2, 1, 1

最终返回堆顶元素值 3。

对于 1, 7, 9 可以插入 2 个值的情况，按照上述步骤，应该依次是：

1. 1, 4, 7, 9
2. 1, 2, 4, 7, 9

最终返回的最大差值是 3。

但是实际情况是，可以插入为 1, 3, 5, 7, 9，最终的最大差值为 2，上面的方案并不是最优解。这里的关键是可以不是二分，而是三等分。

从上面的分析中可以看出，将 $M_i$ 和 $M_{i+1}$ 中插入 k 次锻炼，这两次锻炼之间的最小的难度变为 $\lceil \frac{M_i - M_{i+1}}{k + 1} \rceil$。

经过上面的分析，算法思路如下：

1. 预先算出差值数组
2. 使用深度优先搜索，第 i 个差值插入 $k_i$ 次锻炼，对后续所有情况取最小值即可。计算过程中需要使用map进行缓存。

#### 代码 1

> 这种方法时间复杂度比较高，最终在 Test set 2 TLE 了。

```cpp
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

int t, n, k, m[100005];
// 缓存 dfs 结果
map<int, map<int, int>> mp;

int diff(int d, int k) {
    return int(ceil(d / (k + 1.0)));
}

int dfs(int workout_idx, int k) {
    if (mp.count(workout_idx) && mp[workout_idx].count(k)) {
        return mp[workout_idx][k];
    }

    // 总共 n - 1 个间隔
    if (workout_idx == n - 1 - 1) {
        return mp[workout_idx][k] = diff(m[workout_idx], k);
    }

    int res = INT32_MAX;
    // i 表示用 i 个新的锻炼来划分原有的锻炼
    for (int i = 0; i <= k; i++) {
        int tmp = diff(m[workout_idx], i);

        int sub_value = dfs(workout_idx + 1, k - i);
        // 后面的所有插入情况中，取最优情况
        res = min(res, max(tmp, sub_value));

        // 剪枝：再给此处增加锻炼数没用了，只会造成偏斜越来越严重
        if (tmp <= sub_value) break;
    }

    mp[workout_idx][k] = res;
    return res;
}

int solve() {
    return dfs(0, k);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        mp.clear();
        cin >> n >> k;
        int prev, cur;
        for (int i = 0; i < n; i++) {
            cin >> cur;
            if (i != 0) {
                m[i - 1] = cur - prev;
            }
            prev = cur;
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

#### 解析 2

直接遍历所有可能的解，去判断要生成这个解需要插入的锻炼个数 $K'$ 是否小于 K，如果小于，就可以满足。对解的搜索可以采用二分查找。

锻炼时长 $M_i$, $M_{i+1}$ 需要变为难度 $d$ 至少需要插入 $\lceil \frac{M_{i+1} - M_i}{d} - 1 \rceil$ 个新的锻炼。

#### 代码 2

```cpp
#include <iostream>

using namespace std;

int t, n, k, m[100005], max_diff;
// 单个间隔降到难度 d 至少需要的插入个数
int single_insert_num(int delta_m, int d) {
    int cnt = 0, tmp = 0;
    while (tmp < delta_m) {
        cnt++;
        tmp += d;
    }
    return cnt - 1;
}

// 总体降到难度 d 至少需要的插入个数
int total_insert_num(int d) {
    int res = 0;
    // 总共有 n - 1 个间隔
    for (int i = 0; i < n - 1; i++) {
        res += single_insert_num(m[i], d);
    }
    return res;
}

int solve() {
    int low = 1, high = max_diff, res = max_diff;
    while (low <= high) {
        int mid = (low + high) / 2;
        int k_prime = total_insert_num(mid);
        if (k_prime > k) {
            low = mid + 1;
        } else {
            res = mid;
            high = mid - 1;
        }
    }
    return res;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        max_diff = 0;
        cin >> n >> k;
        int prev, cur;
        for (int i = 0; i < n; i++) {
            cin >> cur;
            if (i != 0) {
                m[i - 1] = cur - prev;
                max_diff = max(max_diff, m[i - 1]);
            }
            prev = cur;
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

### D. Bundling

#### 题目大意

将 N 个大写字符串分组，每个组的有 K 个字符串（输入保证 K 整除 N），每个组的得分为这个组的公共前缀长度，求最大的得分总和。

#### 解析

需要利用 [Trie](https://www.geeksforgeeks.org/trie-insert-and-search/)，也就是前缀树。以 G, G, GO, GO, GOO, GOO, GOOO, GOOO 为例，前缀树长这样：

G (cnt = 8)
|
O (cnt = 6)
|
O (cnt = 4)
|
O (cnt = 2)

第 x 层的 cnt[x] 表示被经过的次数，对前缀长的总贡献为 cnt[x]，分为字符串个数为 K 的组时，其对前缀长的贡献为 cnt[x] / k。

#### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int t, n, k;
string s[100005];

const int ALPHABET_SIZE = 26;
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int cnt[ALPHABET_SIZE] = {0};

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

struct TrieNode *getNode(void) {
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
        pNode->cnt[i] = 0;
    }

    return pNode;
}
void insert(struct TrieNode *root, string key) {
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        (pCrawl->cnt[index])++;
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

int solve() {
    struct TrieNode *root = getNode();
    for (int i = 0; i < n; i++)
        insert(root, s[i]);

    int ans = 0;
    queue<TrieNode *> q;
    q.push(root);
    while (!q.empty()) {
        TrieNode *cur = q.front();
        q.pop();

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (cur->children[i] != NULL) {
                q.push(cur->children[i]);
                ans += cur->cnt[i] / k;
            }
        }
    }

    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```
