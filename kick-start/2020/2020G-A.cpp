#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int t, n;
vector<int> ki, si;
string s;

// 2 + 1 = 3
// kick: 1, 10; START: 5, 15
// 0
// 2 + 2 + 1 = 5

int solve() {
    int pos = 0;
    while ((pos = s.find("KICK", pos)) != string::npos) {
        // cout << "ki add: " << pos << endl;
        ki.push_back(pos++);
    }
    pos = 0;
    while ((pos = s.find("START", pos)) != string::npos) {
        // cout << "si add: " << pos << endl;
        si.push_back(pos++);
    }

    int ans = 0;
    int kiIndex = ki.size() - 1, siIndex = si.size() - 1;

    while (kiIndex >= 0 && siIndex >= 0) {
        // cout << "siIndex: " << siIndex << ", kiIndex: " << kiIndex << endl;;
        if (ki[kiIndex] + 4 <= si[siIndex]) {
            // cout << " ans += " << kiIndex + 1 << endl;
            ans += kiIndex + 1;
            // kiIndex--;
            siIndex--;
        } else {
            // siIndex--;
            kiIndex--;
        }
    }

    return ans;
    // for (int siIndex = si.size() - 1; siIndex; siIndex--) {
    //     if (si[siIndex] + 4 <= ki[kiIndex]) {
    //         ans += siIndex + 1;
    //     }
    // }
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> s;
        ki.clear();
        si.clear();
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}