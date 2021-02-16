# 算法模板

## 快速幂

- AcWing 89

```cpp
// 注意：底数可以取模，但是指数不能取模
// 模的性质：先模后乘（加）等于先乘（加）后模
int qpow(int a, int b, int p) {
    int ans = 1 % p;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % p;
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
```

## lowbit 运算

lowbit 运算返回的数是二进制表示下，原来数的最低位的 1 及后边所有的 0 组成的新的数。

```cpp
lowbit(1010_2) = lowbit(10_2)

lowbit(n) = n & (~n + 1) = n & -n

~n == -1 - n => ~n + 1 == -n

// 预计算 H[2^k] = k，Hash 替代 log 运算
for (int i = 0; i <= 20; i++) H[1 << i] = i;
// 找出整数 n 的二进制表示下所有是 1 的位
while (n > 0) {
    cout << H[n & -n] << " ";
    n -= n & -n;
}
cout << endl;
// 将区间 [1, n] 分为 O(log n) 个小区间，每个区间长度都是当前值的 lowbit
while (x > 0) {
    cout << (x - (x & -x) + 1) << ", "<< x << endl;
    x -= x & -x;
}
```

## 归并排序

```cpp
void merge_sort(int q[], int l, int r)
{
    if (l >= r) return;

    int mid = (l + r) >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];
        else tmp[k ++ ] = q[j ++ ];

    while (i <= mid) tmp[k ++ ] = q[i ++ ];
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];
}
```

## 离散化

如果之后还需要进行查询，可以映射成有序数组。如果之后无需查询，直接映射成无需数组就可以了。

```cpp
// 离散化
void discrete() {
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        // 也可用 STL 的 unique 函数
        if (i == 1 || a[i] != a[i - 1])
            b[++m] = a[i];
    }
}
// 查询 x 映射为哪个 1-m 之间的整数
int query(int x) {
    return lower_bound(b + 1, b + m + 1, x) - b;
}

// ----------

// 也可使用 map，但是一般会比数组慢一些
unordered_map<int, int> mp;
void discrete() {
    for (int i = 1; i <=n; i++) {
        if (!mp.count(a[i]))
            mp[a[i]] = ++m;
    }
}
int query(int x) {
    return mp[x];
}
```

## Trie 树

- AcWing 142 - 144, 1414

```cpp
// 在 Trie 树中，边表示一个字符，节点表示一个前缀，叶子节点表示一个字符串，cnt 用来计数叶子节点表示的字符串出现的次数
// N 为字符串总长度，26 表示字符可能取值范围大小（对于小写字符串为 26，对于二进制数为 2）
// trie[p][ch] = 0 表示叶子节点，为了语义上的一致性，取 p = 1 作为根节点，初始情况不插入任何字符串，就已经有一个节点了
// 也可以将 p = 0 作为根节点，++tot 改为 tot++ 即可
int trie[N][26], tot = 1, cnt[N], n, m;
void insert(string s) {
    int len = s.length(), p = 1;
    for (int k = 0; k < len; k++) {
        int ch = s[k] - 'a';
        if (trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    cnt[p]++;
}
int search(string t) {
    int len = t.length(), p = 1, ans = 0;
    for (int k = 0; k < len; k++) {
        p = trie[p][t[k] - 'a'];
        if (p == 0) return ans;
        ans += cnt[p];
    }
    return ans;
}
```

## 邻接表模板

邻接表最简单的方法是直接用 `vector` 存储，但是用数组存储速度更快，也有一些优点（快速找到反向边），参考[我的分享](https://www.acwing.com/blog/content/4689/)。

- AcWing 257

```cpp
// N, M 分别表示点数和边数，注意如果是无向图的话 M 一定要乘 2，否则会数组越界

// head[x] = m 表示点 x 的邻接表的表头是编号为 m 的边
// ver[m] 表示编号为 m 的边的终点
// edge[m] 表示编号为 m 的边的权值
int head[N], ver[M], edge[M], Next[M], tot;

// 加入有向边 (x, y)，权值为 z
void add(int x, int y, int z) {
    // 真实数据
    ver[++tot] = y, edge[tot] = z;
    // 在表头 x 处插入
    Next[tot] = head[x], head[x] = tot;
}

// 访问从 x 出发的所有边
for (int i = head[x]; i; i = Next[i]) {
    int y = ver[i], z = edge[i];
    // 找到了一条有向边 (x, y)，权值为 z
}
```

## 最大公约数

```cpp
// 欧几里得算法
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
```

另外，最小公倍数 lcm(a, b) = a * b / gcd(a, b)。

## 并查集

```cpp
// sz 表示节点的秩，这里定义为节点的元素个数
int fa[N], sz[N], n;
void init() {
    // 初始化
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
// Get 操作，使用「路径压缩」+「按秩合并」，时间复杂度为反阿克曼函数，可以认为是常数
int get(int x) {
    if (x == fa[x]) return x;
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = get(fa[x]);
}
// Merge 操作，同上，可以认为时间复杂度为常数
void merge(int x, int y) {
    int fx = get(x), fy = get(y);
    if (fx == fy) return;
    if (sz[fx] < sz[fy]) {
        fa[fx] = fy;
        sz[fy] += sz[fx];
    } else {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

// 一定记得初始化并查集
init();
```

另外还有「边带权」和「拓展域」的并查集，在原有并查集的基础上维护一些具有传递关系的属性。

## 树状数组

RMQ 常用算法，参见蓝书 0x42。`c[x]` 保存序列 a 的区间 `[x - lowbit(x) + 1, x]` 中所有数的和。`c[x]` 的父节点为 `c[x + lowbit(x)]`

支持「单点增加」和「区间查询」，结合差分可以支持「区间增加」。

```cpp
// 查询前缀和：查询序列 a 第 1~x 个数的和
int ask(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
}
// 单点增加：给序列中的一个数 a[x] 加上 y
// 算法：自下而上每个节点都要增加 y
void add(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}
```

## 线段树

RMQ 常用算法，树状数组基于区间划分，线段树则是基于分治。

```cpp
struct SegmentTree {
    int l, r;
    int dat;
} t[N * 4];

// 线段树的建树，时间复杂度：O(N)
// p 表示节点编号，[l, r] 表示节点所代表的区间
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    // 叶节点，表示单个元素
    if (l == r) {
        t[p].dat = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    // 左子节点：编号为 2*p，代表区间 [l, mid]
    build(2 * p, l, mid);
    // 右子节点：编号为 2*p+1，代表区间 [mid+1, r]
    build(2 * p + 1, mid + 1, r);
    // 从下往上合并更新信息
    t[p].dat = max(t[2 * p].dat, t[2 * p + 1].dat);
}

// 调用入口
build(1, 1, n);

// 线段树的单点修改，时间复杂度：O(log N)
// 将 a[x] 的值修改为 v
void change(int p, int x, int v) {
    // 找到叶节点
    if (t[p].l == t[p].r) {
        t[p].dat = v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    // x 属于左半区间
    if (x <= mid) change(2 * p, x, v);
    // x 属于右半区间
    else
        change(2 * p + 1, x, v);
    // 从下往上合并更新信息
    t[p].dat = max(t[2 * p].dat, t[2 * p + 1].dat);
}

// 调用入口
change(1, x, v);

// 线段树的区间查询，时间复杂度：O(log N)
// 查询序列 a 在区间 [l, r] 上的最大值
int ask(int p, int l, int r) {
    // 查询区间 [l, r] 完全包含节点 p 所代表的的区间
    if (l <= t[p].l && r >= t[p].r) return t[p].dat;
    int mid = (t[p].l + t[p].r) >> 1;
    // 负无穷大
    int val = -(1 << 30);
    // 左子节点 [t[p].l, mid] 与查询 [l, r] 有重合
    if (l <= mid) val = max(val, ask(2 * p, l, r));
    // 右子节点 [mid+1, t[p].r] 与查询 [l, r] 有重合
    if (r >= mid + 1) val = max(val, ask(2 * p + 1, l, r));
    return val;
}
```

### 支持区间修改的线段树（延迟标记）

区间修改的时间复杂度可以通过延迟标记从 O(N) 降为 O(log N)。

```cpp
// 注意：有延迟标记的节点，本身已经完成了数据更新，只是没有传递给子节点
struct SegmentTree {
    int l, r;
    long long dat, flag;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define dat(x) tree[x].dat
#define flag(x) tree[x].flag
} tree[N * 4];
int a[N];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if (l == r) {
        dat(p) = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * p, l, mid);
    build(2 * p + 1, mid + 1, r);
    dat(p) = dat(2 * p) + dat(2 * p + 1);
}
void spread(int p) {
    // 节点 p 有延迟标记的话
    if (flag(p)) {
        // 更新左子节点信息，延迟值 * 区间长度等于节点的增加量
        dat(2 * p) += flag(p) * (r(2 * p) - l(2 * p) + 1);
        // 更新右子节点信息
        dat(2 * p + 1) += flag(p) * (r(2 * p + 1) - l(2 * p + 1) + 1);
        // 给左子节点打延迟标记
        flag(2 * p) += flag(p);
        // 给右子节点打延迟标记
        flag(2 * p + 1) += flag(p);
        // 清除 p 的标记
        flag(p) = 0;
    }
}

void change(int p, int l, int r, int d) {
    // 完全覆盖
    if (l <= l(p) && r >= r(p)) {
        // 更新节点信息，每个节点增加量 d * 区间长度 = 节点增加量
        dat(p) += (long long)d * (r(p) - l(p) + 1);
        // 给节点打延迟标记
        flag(p) += d;
        return;
    }
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = (l(p) + r(p)) >> 1;
    // 和左子节点有相交部分
    if (l <= mid) change(2 * p, l, r, d);
    // 和右子节点有相交部分
    if (r >= mid + 1) change(2 * p + 1, l, r, d);
    dat(p) = dat(2 * p) + dat(2 * p + 1);
}

long long ask(int p, int l, int r) {
    if (l <= l(p) && r >= r(p)) return dat(p);
    // 因为即将访问下面的节点了，必须先下传延迟标记
    spread(p);
    int mid = (l + r) >> 1;
    long long val = 0;
    if (l <= mid) val += ask(2 * p, l, r);
    if (r >= mid + 1) val += ask(2 * p + 1, l, r);
    return val;
}
```

- AcWing 243

## 质筛选

```cpp
// Eratosthenes 筛法
void primes(int n) {
    // 合数标记
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; i++) {
        if (v[i]) continue;
        cout << i << endl;
        for (int j = i; j <= n/i; j++) v[i*j] = 1;
    }
}
```

## 致谢

本模板多数出自《算法竞赛进阶指南》（蓝书）和 AcWing 社区，非常感谢蓝书作者、AcWing 社区的 y 总和其他的小伙伴。
