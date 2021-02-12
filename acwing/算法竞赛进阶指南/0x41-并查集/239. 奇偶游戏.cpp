/*
sum 表示序列 S 的前缀和，那么：
- S[l-r] 有偶数个 1，等价于 sum[l - 1] 与 sum[r] 奇偶性相同
- S[l-r] 有奇数个 1，等价于 sum[l - 1] 与 sum[r] 奇偶性不同

这题输入数据范围为 10^9，但是总个数为 10^4，因此可以离散化

离散化后 l-1 和 r 的值分别是 x 和 y，ans 表示询问的回答，0 代表偶数个（奇偶性相同），1代表奇数个（奇偶性不同）

有边带权和扩展域两种做法
1. 边带权：
    d[x] 表示 x 到和根节点 root 的奇偶性关系，初始化为 d[x] = 0 表示自己和自己的奇偶性相同
    x 和 y 如果在同一个集合里面，执行 get(x) 和 get(y) 之后，d[x] xor d[y] 即为结果，如果不等于 ans，则说明小 A 撒谎
    x 和 y 如果不在同一个集合里面，根节点分别为 p 和 q，可知将 fa[p] = p 之后有关系 ans = d[x] xor d[y] xor d[p]，因此设置 d[p] = ans xor d[x] xor d[y]
2. 扩展域：
    将变量 x 拆成 x_odd 和 x_even，每次根据 ans = 0 合并 x_odd 与 y_odd，x_even 与 y_even；或者根据 ans = 1 合并 x_odd 与 y_even，x_even 与 y_odd
    扩展域可以维护关系的传递性
    每次添加新关系前检查是否矛盾即可
*/
#include <iostream>
#include <unordered_map>
using namespace std;
const int M = 1e4 + 10;

int n, m, l, r, tot;
string s;
// 离散化
unordered_map<int, int> mp;
int discrete(int x) {
    if (!mp.count(x))
        mp[x] = ++tot;
    return mp[x];
}
// sz 表示节点的秩，这里定义为节点的元素个数
int fa[M], sz[M], d[M];
void init() {
    // 初始化
    for (int i = 1; i <= M; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
// Get 操作
int get(int x) {
    if (x == fa[x]) return x;
    // 递归计算 d[fa[x]]
    int root = get(fa[x]);
    // 再更新 d[x]
    d[x] ^= d[fa[x]];
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = root;
}
int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; i++) {
        cin >> l >> r >> s;
        int ans = s == "even" ? 0 : 1;
        int x = discrete(l - 1), y = discrete(r);
        int p = get(x), q = get(y);
        // 已经在同一个集合内
        if (p == q) {
            if (d[x] ^ d[y] != ans) {
                cout << i - 1 << endl;
                return 0;
            }
        } else {
            // 不在同一个集合，合并
            fa[p] = q;
            d[p] = d[x] ^ d[y] ^ ans;
        }
    }
    // 没有矛盾
    cout << m << endl;
    return 0;
}