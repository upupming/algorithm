/*
计算过程非常简单，重点在于这些大臣怎么排。

右手的数越小，同等位置条件下获得的奖励越多。
最优方案肯定是让那些右手的数较小的放在前面。

左手的数越小，同等情况下后面的大臣获得的奖励越少。
最优方案肯定是让那些左手的数较小的放在前面。

先看最后一个大臣，一旦这个大臣确定了，那么前面所有大臣的左手乘积可以确定，这个大臣的右手又是确定的。
这个大臣的得分是：
    (所有大臣左手乘积 / 此大臣左手) / 此大臣右手
所以只需要最大化(此大臣左手 * 此大臣右手)的值即可。

最终的排序应该就是按照左手 * 右手进行从小到大排序即可。
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 高精度参考：https://www.acwing.com/blog/content/539/

vector<int> mul(vector<int> a, int b) {
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

vector<int> div(vector<int> a, int b) {
    vector<int> c;
    bool is_first = true;
    for (int i = a.size() - 1, t = 0; i >= 0; i--) {
        t = t * 10 + a[i];
        int x = t / b;
        if (!is_first || x) {
            is_first = false;
            c.push_back(x);
        }
        t %= b;
    }
    reverse(c.begin(), c.end());
    return c;
}

vector<int> max_vec(vector<int> a, vector<int> b) {
    if (a.size() > b.size()) return a;
    if (a.size() < b.size()) return b;
    if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend())) return a;
    return b;
}

int n, a, b;
// pair<乘积, pair<左手, 右手>>
pair<int, pair<int, int>> c[1010];
int main() {
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++)
        cin >> c[i].second.first >> c[i].second.second, c[i].first = c[i].second.first * c[i].second.second;
    sort(c, c + n);
    vector<int> acc(1, 1), ans(1, 0);
    acc = mul(acc, a);
    for (int i = 0; i < n; i++) {
        ans = max_vec(ans, div(acc, c[i].second.second));
        acc = mul(acc, c[i].second.first);
    }
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i];
    cout << endl;
    return 0;
}