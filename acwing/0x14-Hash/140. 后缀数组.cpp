/*
快排 + Hash + 二分
比较两个后缀的时候，二分两个后缀出现不同的下标，将 O(n) 的比较时间降为 O(log n)
*/
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;
const int P = 131, N = 300010;
typedef unsigned long long ULL;

string s;
ULL f[N], sa[N], p[N];
int n;
ULL get(int l, int r) {
    return f[r] - f[l - 1] * p[r - l + 1];
}
int getMaxCommonPrefix(int i, int j) {
    // 相等前缀长度：从第一个字符就不相同，为 0；一直到最后一个字符，为 min(n - i + 1, n - j + 1)
    int l = 0, r = min(n - i + 1, n - j + 1);
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (get(i, i + mid - 1) == get(j, j + mid - 1))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
int main() {
    cin >> s;
    p[0] = 1;
    n = s.length();
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * P + (s[i - 1] - 'a' + 1);
        p[i] = p[i - 1] * P;
        sa[i] = i;
    }
    sort(sa + 1, sa + n + 1,
         [](int i, int j) -> bool {
             int l = getMaxCommonPrefix(i, j);
             int av = i + l > n ? INT_MIN : s[i + l - 1];
             int bv = j + l > n ? INT_MIN : s[j + l - 1];
             return av < bv;
         });

    for (int i = 1; i <= n; i++) cout << sa[i] - 1 << " ";
    cout << endl;
    for (int i = 1; i <= n; i++) {
        if (i == 1)
            cout << "0";
        else
            cout << " " << getMaxCommonPrefix(sa[i - 1], sa[i]);
    }
    cout << endl;
    return 0;
}