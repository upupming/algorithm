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
  - [Round B](#round-b)
    - [A. Bike Tour](#a-bike-tour)
      - [题目大意](#题目大意-4)
      - [解析](#解析-3)
      - [代码](#代码-3)
    - [B. Bus Routes](#b-bus-routes)
      - [题目大意](#题目大意-5)
      - [解析](#解析-4)
      - [代码](#代码-4)
    - [C. Robot Path Decoding](#c-robot-path-decoding)
      - [题目大意](#题目大意-6)
      - [解析](#解析-5)
      - [代码](#代码-5)
    - [D. Wandering Robot](#d-wandering-robot)
      - [题目大意](#题目大意-7)
      - [解析](#解析-6)
      - [代码](#代码-6)

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

## Round B

### A. Bike Tour

#### 题目大意

N 个数，如果一个数比它两边的数都大，那么就是一个 peak，计算 peak 的总数。

#### 解析

遍历一遍数组，与周围比较即可。第 1 个和第 N 个数肯定不是 peak。

#### 代码

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

int t, n, h[200];

int solve() {
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        if (h[i] > h[i - 1] && h[i] > h[i + 1]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

### B. Bus Routes

#### 题目大意

N 条公交路线，第 i 个路线每 $X_i$ 天开一次（在第$X_i, 2X_i, \cdots$天开），要把所有公交路线在 $D$ 天内按照编号由小到大的顺序都乘一遍，求乘第一个公交的最晚时间。同一天可乘多个公交，保证 D 天内是可完成这个任务的。

#### 解析

对于不需要保证公交乘坐顺序的情况。求 $X_i$ 小于等于 $D$ 但是离 $D$ 最近的数即可，得到一个新的数组之后，数组的最小值就是答案。注意 D 最大可到 $10^{21}$，超过 int32 范围，需要用 long long。

对于需要考虑乘坐顺序的情况，需要从最后一个公交路线开始选择，这个公交路线的乘坐时间一旦确定，之前的公交路线需要都在此时间之前（<=关系），这可以通过更新 D 为此公交路线的乘坐时间即可。

#### 代码

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

int t, n;
long long d, x[1005];

long long solve() {
    long long ans = __LONG_LONG_MAX__;
    for (int i = n - 1; i >= 0; i--) {
        // 离 d 最近的 x[i] 的倍数
        x[i] = d / x[i] * x[i];
        ans = min(ans, x[i]);
        d = min(d, x[i]);
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> d;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
```

### C. Robot Path Decoding

#### 题目大意

$10^9 \times10^9$ 的网格，从 $(1, 1)$ 坐标开始，经过一系列行走的指令，求最终到达的坐标。关键在于对指令字符串的处理，N, S, E, W 表示四个方向，可以使用数字表示同一指令的多次重复。注意坐标 $10^9$ 再往右走会回到 $1$。

```txt
2(NWE) is equivalent to NWENWE.
3(S2(E)) is equivalent to SEESEESEE.
EEEE4(N)2(SS) is equivalent to EEEENNNNSSSS.
```

#### 解析

注意到越是里面的括号优先级越高。可以使用符号栈的思想，遇到`)`时弹出栈内元素直到出现出现`2(`这样的倍数，然后将展开成变成不带数字的重复符号重新压入即可。

以 `2(W2(EE)W))` 为例，栈中内容变化如下：

```txt
2(W2(EE
2(W
2(WEEEE
2(WEEEEW
WEEEEWWEEEEW
```

另外注意到指令执行的顺序是不影响结果的，可以将括号内的先执行也没有问题。注意到指令展开之后的长度是没有限制的，而只限制了输入字符串的长度，因此需要对内部括号的计算结果进行缓存用于外部括号的计算，这个缓存和利用缓存的过程通过栈 `xs` 和 `ys` 实现。

#### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int t;
long long bound = 1000000000;
string cmd;

long long mod(long long a, long long b) {
    long long ret = a % b;
    return ret >= 0 ? ret : ret + b;
}

void run(const char& c, long long& x, long long& y) {
    if (c == 'N') y = mod((y - 1), bound);
    if (c == 'S') y = mod((y + 1), bound);
    if (c == 'E') x = mod((x + 1), bound);
    if (c == 'W') x = mod((x - 1), bound);
}

pair<int, int> solve() {
    stack<char> moves;
    stack<long long> xs, ys;
    long long x = 0, y = 0;

    for (int i = 0; i < cmd.length(); i++) {
        if (cmd[i] == ')') {
            long long xx = xs.top(), yy = ys.top();
            xs.pop();
            ys.pop();

            while (moves.top() != '(') {
                // 执行当前括号内的所有命令，指令执行顺序不影响结果
                char c = moves.top();
                run(c, xx, yy);
                moves.pop();
            }
            // `(` 出栈
            moves.pop();
            // 倍数出栈
            int times = moves.top() - '0';
            moves.pop();

            if (!xs.empty()) {
                xs.top() = mod(xs.top() + xx * times, bound);
                ys.top() = mod(ys.top() + yy * times, bound);
            } else {
                x = mod(x + xx * times, bound);
                y = mod(y + yy * times, bound);
            }

        } else {
            if (cmd[i] == '(') {
                xs.push(0);
                ys.push(0);
            }
            moves.push(cmd[i]);
        }
    }

    while (!moves.empty()) {
        char c = moves.top();
        run(c, x, y);
        moves.pop();
    }

    return make_pair(x + 1, y + 1);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> cmd;
        pair<int, int> ans = solve();
        printf("Case #%d: %d %d\n", i, ans.first, ans.second);
    }
    return 0;
}
```

### D. Wandering Robot

#### 题目大意

宽度和高度分别为 W 和 H 的网格中间从左上角 (L, U) 到 (R, D) 的部分是 hole。现在要从左上角走到右下角，每次选择右和下的概率相同，在边界的时候只有一个方向可走，求不落到 hole 里面的概率。

#### 解析

hole 的地方失败概率为1，右下角如果不是 hole 的话，失败概率为0，其他地方失败概率为右边和下边的各一半之和。

使用带缓存的 dfs 会在 Test 2 上 MLE：

```cpp
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int t, w, h, l, u, r, d;
map<int, map<int, float>> mp;

// 返回失败概率
float dfs(int ww, int hh) {
    if (mp.count(ww) && mp[ww].count(hh)) return mp[ww][hh];

    float ans;

    if (ww >= l && ww <= r && hh >= u && hh <= d)
        ans = 1;
    else if (ww == w) {
        if (hh == h)
            ans = 0;
        else
            ans = dfs(ww, hh + 1);
    } else if (hh == h)
        ans = dfs(ww + 1, hh);
    else {
        ans = 0.5 * dfs(ww + 1, hh) + 0.5 * dfs(ww, hh + 1);
    }

    mp[ww][hh] = ans;
    return ans;
}

float solve() {
    return 1 - dfs(1, 1);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        mp.clear();
        cin >> w >> h >> l >> u >> r >> d;
        printf("Case #%d: %f\n", i, solve());
    }
    return 0;
}
```

使用动态规划。先从最后一行，从右往左计算每个点的失败概率，然后计算上一行的时候只需要用到下一行，因此可以节约存储空间，最终的空间复杂度仅为 $O(W)$，时间复杂度为 $O(WH)$。注意顺序是从下往上，从右往左以实现复用，在计算第 i 行第 j 列的时候，用到的两个概率中，第 j+1 列是这一行的，第 j 列是下一行的。这个复杂度仍然会 TLE：

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

// dp 中存放失败概率
int t, w, h, l, u, r, d;
float dp[100005];

float solve() {
    // 如果右下角是 hole
    if (w == r && h == d) return 0;
    dp[w] = 0;
    // 处理最后一行
    for (int i = w - 1; i >= 1; i--) {
        if (h == d && i >= l && i <= r)
            dp[i] = 1;
        else
            dp[i] = dp[i + 1];
    }
    // 处理上面的行
    for (int i = h - 1; i >= 1; i--) {
        for (int j = w; j >= 1; j--) {
            if (i >= u && i <= d && j >= l && j <= r)
                dp[j] = 1;
            else if (j != w) {
                dp[j] = 0.5 * dp[j + 1] + 0.5 * dp[j];
            }
        }
    }

    return 1 - dp[1];
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> w >> h >> l >> u >> r >> d;
        printf("Case #%d: %f\n", i, solve());
    }
    return 0;
}
```

最终还是参考了官方的分析，将成功的概率转换为经过绿色方块的概率，这些绿色方块是想要到达右下角，就必须经过的方块：

![20200624214240](https://picgo-1256492673.cos.ap-chengdu.myqcloud.com/20200624214240.png)

根据[这里](https://www.geeksforgeeks.org/maths-behind-number-of-paths-in-matrix-problem/)的分析，从坐标 (1, 1) 到 (ww, hh) 需要走 (ww - 1 + hh - 1) 步，走 (ww - 1 + hh - 1) 步总共有 $A = 2^{(ww - 1 + hh - 1)}$ 种走法；但是要求有 (ww - 1) 步向右，(hh - 1) 步向下，所以总共有 $B = C_{(ww - 1 + hh - 1)}^{(ww - 1)}$ 种走法，因此走到格子 (ww, hh) 的概率为 $\frac{B}{A}$。

由于分子分母数据太大，需要取对数再求指数作为结果：

$$
\frac{C_n^k}{2^n} = n!/[k!(n-k)!]/2^n = 2^{\log_2 n! - \log_2 k! -\log_2(n-k)! - n}
$$

先对 1 到 n 的对数进行预处理用于后续的计算，最终的复杂度为对角线长度 $O(\max{(W, H)})$。

X 的坐标为 (L - 1, D + 1)，同理右上角的对角线最左下的方格的坐标为 (R + 1, U - 1)。

需要注意的是，右边界和下边界的情况下，由于只有一种后续情况，概率需要另算。计算方式为，当前格子只能从离他最近前一步的两个格子的情况进行推导，比如下面的例子中，2处的概率为1的概率加上3的概率的一半：

```txt
xxx
x3x
12O
```

#### 代码

```cpp
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int t, w, h, l, u, r, d;
const int max_n = 200005;
double log_2_factorial[max_n], last_h[max_n], last_w[max_n];

double cal(int n, int k) {
    return pow(2, log_2_factorial[n] - log_2_factorial[k] - log_2_factorial[n - k] - n);
}

double solve() {
    double ans = 0;

    // 计算边界情况的概率
    // (1. h)
    last_h[1] = 0.5 * cal(h - 1 + 1 - 2, 0);
    // (2, h) 到 (w, h)
    for (int i = 2; i <= w; i++) {
        last_h[i] = last_h[i - 1] + 0.5 * cal(h - 1 + i - 2, i - 1);
    }
    // (w, 1)
    last_w[1] = 0.5 * cal(w - 1 + 1 - 2, 0);
    // (w, 2) 到 (w, h)
    for (int i = 2; i <= h; i++) {
        last_w[i] = last_w[i - 1] + 0.5 * cal(w - 1 + i - 2, i - 1);
    }

    int left_sum = l - 1 + d + 1, right_sum = r + 1 + u - 1;
    // 左下角
    for (int i = l - 1, j = d + 1; i >= 1 && j <= h; i--, j++) {
        if (j == h) {
            ans += last_h[i];
        } else
            // 总共需要 left_sum - 2 步，i - 1 步向右
            ans += cal(left_sum - 2, i - 1);
    }
    // 右上角
    for (int i = r + 1, j = u - 1; i <= w && j >= 1; i++, j--) {
        if (i == w) {
            ans += last_w[j];
        } else
            ans += cal(right_sum - 2, i - 1);
    }

    return ans;
}

int main() {
    cin >> t;

    log_2_factorial[0] = 0;
    for (int i = 1; i < max_n; i++) {
        log_2_factorial[i] = log_2_factorial[i - 1] + log2(i);
    }

    for (int i = 1; i <= t; i++) {
        cin >> w >> h >> l >> u >> r >> d;
        printf("Case #%d: %lf\n", i, solve());
    }
    return 0;
}
```
