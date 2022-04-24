#include <algorithm>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
int t;
LL a;
string s;
#define N 3000000
LL b[N];
int n;

int solve() {
    int ans = 0;
    for (LL b = 1; b <= a; b++) {
        auto s = to_string(b);
        auto t = to_string(b);
        reverse(t.begin(), t.end());
        if (s == t && (a % b == 0)) ans++;
    }
    return ans;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> a;
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
