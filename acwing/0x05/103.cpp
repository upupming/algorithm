/*
虽然 a, b, c 的范围都是 10^9，但是最多只会有 2 * 10^5 * 3 个数
可以使用离散化缩小数据范围，映射数组 d[i] = j 表示将语言的映射值 i (2 * 10^5 * 3) 代表真实的语言 j ([1, 10^9])，利用二分搜索 query(j) = i

首先将 a 扫一遍，构建 d 数组。同时建立 e 数组表示语言被多少科学家所懂得。
然后分别扫描 b 和 c 即可。感觉其实也可以不用构建 d，直接使用 map 实现。
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int n, m, a[200010], b[200010], c[200010], d[200010], e[200010], t;
unordered_map<int, int> ma;

// 直接使用 map 求解
void solve1() {
    for (int i = 0; i < n; i++) ma[a[i]]++;
    vector<int> ans;
    int max = 0;
    // 有很多可能的听懂人数最多的，维护一个 vector
    for (int i = 0; i < m; i++) {
        if (ma[b[i]] > max)
            max = ma[b[i]], ans.clear(), ans.push_back(i);
        else if (ma[b[i]] == max)
            ans.push_back(i);
    }
    max = 0;
    int maxIdx = 0;
    // 从 vector 里面抽出看懂字幕人数最多的
    for (int i = 0; i < ans.size(); i++) {
        if (ma[c[ans[i]]] > max) {
            max = ma[c[ans[i]]];
            maxIdx = ans[i];
        }
    }
    cout << maxIdx + 1 << endl;
}

int query(int x) {
    return lower_bound(d, d + t, x) - d;
}
// 离散化
void solve2() {
    sort(a, a + n);
    // 使用离散化求解，构建一个数组，将原有值映射到较小的范围
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[i] != a[i - 1]) d[t++] = a[i];
    }
    // 构建 e 数组
    for (int i = 0; i < n; i++) e[query(a[i])]++;
    vector<int> ans;
    int max = 0;
    // 有很多可能的听懂人数最多的，维护一个 vector
    for (int i = 0; i < m; i++) {
        int q = query(b[i]);
        if (d[q] == b[i]) {
            if (e[q] > max)
                max = e[q], ans.clear(), ans.push_back(i);
            else if (e[q] == max)
                ans.push_back(i);
        }
    }
    max = 0;
    int maxIdx = 0;
    // 从 vector 里面抽出看懂字幕人数最多的
    for (int i = 0; i < ans.size(); i++) {
        int q = query(c[ans[i]]);
        // 如果 c[i] = 7，但是 a 里面没有 7，
        // 有可能找出来的 q 是大于 7 的元素下标，不应该统计
        if (d[q] == c[ans[i]]) {
            if (e[q] > max) {
                max = e[q];
                maxIdx = ans[i];
            }
        }
    }
    cout << maxIdx + 1 << endl;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> b[i];
    for (int i = 0; i < m; i++) cin >> c[i];
    solve2();
    return 0;
}