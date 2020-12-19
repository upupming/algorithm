/*
感觉暴力枚举应该可以过
*/
#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
int n;
set<PIII> s;
set<PII> ans;
// 没有方向：0
// 上下：1
// 左右：2
int main() {
    cin >> n;

    // 找规律即可
    if (n % 2) {
        cout << (n * n + 3) / 2 + 2 * n << endl;
    } else {
        cout << (n / 2 + 1) * (n / 2 + 1) << endl;
    }

    // s.emplace(make_pair(0, 0), 0);
    // while (n--) {
    //     auto t = s;
    //     s.clear();
    //     for (auto p : t) {
    //         int x = p.first.first, y = p.first.second, dir = p.second;
    //         if (dir == 0) {
    //             // 上下左右都可以
    //             s.emplace(make_pair(x - 1, y), 1);
    //             s.emplace(make_pair(x + 1, y), 1);
    //             s.emplace(make_pair(x, y - 1), 2);
    //             s.emplace(make_pair(x, y + 1), 2);
    //         } else if (dir == 1) {
    //             // 只能左右走
    //             s.emplace(make_pair(x, y - 1), 2);
    //             s.emplace(make_pair(x, y + 1), 2);
    //         } else if (dir == 2) {
    //             // 只能上下走
    //             s.emplace(make_pair(x - 1, y), 1);
    //             s.emplace(make_pair(x + 1, y), 1);
    //         }
    //     }
    // }
    // for (auto p : s) {
    //     int x = p.first.first, y = p.first.second;
    //     ans.emplace(x, y);
    // }
    // cout << ans.size() << endl;
    return 0;
}