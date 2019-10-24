#include <iostream>
#include <vector>

using namespace std;

int n, m, l, a[205], dp[10005], maxlen, index[205];
vector<int> b;

// 关键思想在于：dp[i] = max(dp[i], dp[j] + 1)，j 是【所有小于 【i 的下标代表的数】的数下标】
// 由基本的最长子序列问题演化而来，增加一个 index[...] 来找到数的下标

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        index[a[i]] = i;
    }
    cin >> l; int tmp;
    for (int i = 0; i < l; i++) {
        cin >> tmp;
        if (a[index[tmp]] == tmp) b.push_back(tmp); 
    }
    for (int i = 0; i < b.size(); i++) {
        // 初始化，自己构成的子序列长度就为 1
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (index[b[j]] <= index[b[i]]) dp[i] = max(dp[i], dp[j] + 1);
        }
        maxlen = max(maxlen, dp[i]);
    }
    cout << maxlen << endl;
    return 0;
}