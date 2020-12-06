/*
贪心
最后一头牛选 i 的话，那么它的风险值为 (sum(w) - wi) - si
最小化风险，意味着最大化 (wi + si)
所以，直接按照排序 w+s 对所有牛排序即可
跟国王的奖励一样
*/
#include <algorithm>
#include <iostream>
using namespace std;

int n;
pair<int, int> ws_w[50010];
long long sum[50010];
int main() {
    cin >> n;
    int w, s;
    for (int i = 1; i <= n; i++) {
        cin >> w >> s;
        ws_w[i] = {w + s, w};
    }
    sort(ws_w + 1, ws_w + n + 1);
    for (int i = 1; i <= n; i++)
        sum[i] = ws_w[i].second + sum[i - 1];

    long long ans = -1e10;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, sum[i - 1] - (ws_w[i].first - ws_w[i].second));
    }
    cout << ans << endl;
    return 0;
}