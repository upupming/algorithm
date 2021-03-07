#include <cstring>
#include <iostream>
#include <unordered_set>
using namespace std;
const int N = 110;

int a, n, f[N];

int sg(int x) {
    if (f[x] != -1) return f[x];

    unordered_set<int> s;
    // 枚举可以变成那些局面
    for (int i = 0; i < x; i++) {
        for (int j = 0; j <= i; j++) {
            s.insert(sg(i) ^ sg(j));
        }
    }

    for (int i = 0;; i++) {
        if (!s.count(i)) return f[x] = i;
    }
}

int main() {
    cin >> n;
    memset(f, -1, sizeof f);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a;
        ans ^= sg(a);
    }
    if (ans) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}
