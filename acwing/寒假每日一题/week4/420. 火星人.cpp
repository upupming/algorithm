#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e4 + 10;

int n, a[N], m;
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        // 做法一：直接使用 next_permutation
        // next_permutation(a, a + n);
        // 做法二：自己实现 next_permutation
        int j = n - 1, s, t;
        while (a[j - 1] > a[j]) j--;
        s = j - 1, t = j;
        while (t < n && a[t] > a[s]) t++;
        // cout << s << " " << t << endl;
        swap(a[s], a[t - 1]);
        reverse(a + s + 1, a + n);
        // for (int i = 0; i < n; i++) cout << a[i] << " ";
        // cout << endl;
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    return 0;
}