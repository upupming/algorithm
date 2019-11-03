#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int t, n, s, a[100010], sum[100010];

// 前缀和枚举只能过小数据
// TODO: 利用线段树过大数据
int solve() {
    int maxS = 0;
    for (int L = 0; L < n; L++) {
        int sum = 0;
        map<int, int> mp;
        for (int R = L; R < n; R++) {
            mp[a[R]]++;
            if (mp[a[R]] <= s) sum++;
            else if (mp[a[R]] == s + 1) sum -= s;
            maxS = max(maxS, sum);
        }
    }
    return maxS;
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d %d", &n, &s);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}