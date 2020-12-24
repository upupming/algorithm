#include <cmath>
#include <iostream>

using namespace std;

int n, m, t[100010], k, maxV;
string op[100010];

int cal(string op, int a, int b) {
    if (op == "OR")
        return a | b;
    else if (op == "XOR")
        return a ^ b;
    else if (op == "AND")
        return a & b;
    return -1;
}

int main() {
    cin >> n >> m;
    maxV = m;
    for (int i = 0; i < n; i++) {
        cin >> op[i] >> t[i];
        maxV = max(maxV, t[i]);
    }
    int ans = 0, choice = 0;
    k = log2(maxV);
    // cout << k << endl;
    // 从最高位依次枚举每一位可能的情况
    // 这里为什么是 k 而不是 k - 1: 因为 log 3 = 1 （k = 1）但是实际上它是有 2 位的，多一位总是没有问题的，因为 0 和 0 的所有位运算结果都是 0 本身
    for (int i = k; i >= 0; i--) {
        int res1 = 1, res0 = 0;
        for (int j = 0; j < n; j++) {
            res1 = cal(op[j], res1, (t[j] >> i) & 1), res0 = cal(op[j], res0, (t[j] >> i) & 1);
        }
        // cout << i << ", " << res1 << ", " << res0 << endl;
        if (res0 == 1)
            ans += (1 << i);
        else if (res1 == 1 && choice + (1 << i) <= m)
            ans += (1 << i), choice += (1 << i);
    }
    cout << ans << endl;
    return 0;
}