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
