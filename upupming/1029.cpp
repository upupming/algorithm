#include <iostream>

using namespace std;

long long n, m, a[200010], b[200010];

int main () {
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    scanf("%lld", &m);
    for (int i = 0; i < m; i++) scanf("%lld", &b[i]);
    int minPos = (n + m - 1) / 2, cnt = 0;
    int i = 0, j = 0;
    bool aUsed = false, bUsed = false;
    // cout << minPos << endl;
    while (cnt != minPos + 1) {
        // a 数组被数完了，还往下数的话
        if (i == n) { aUsed = true; j++;}
        else if (j == m) { bUsed = true; i++; }
        else if (a[i] <= b[j]) i++;
        else j++;
        cnt++;
    }
    if (aUsed) cout << b[j - 1] << endl;
    else if (bUsed) cout << a[i - 1] << endl;
    else cout << max(a[i - 1], b[j - 1]) << endl;
}

/**
5 15 16 17 18 19
4 11 12 13 14

4 11 12 13 14
5 15 16 17 18 19
*/