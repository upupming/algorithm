#include <iostream>
#include <algorithm>

using namespace std;

int t, s[100005], n, p, sum[100005];

int solve() {
    sort(s, s + n);
    sum[0] = 0;
    for (int i = 0; i < n; i++) sum[i + 1] = sum[i] + s[i];
    int minCoachingTime = 0x3FFFFFFF;
    for (int i = p - 1; i < n; i++) {
        // 需要达到的相同技能
        int skill = s[i];
        // 需要学习的人员当前的总技能和
        int totalSkill = sum[i] - sum[i - (p - 1)];
        minCoachingTime = min(minCoachingTime, skill * (p - 1) - totalSkill);
    }
    return minCoachingTime;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> p;
        for (int i = 0; i < n; i++) cin >> s[i];
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}