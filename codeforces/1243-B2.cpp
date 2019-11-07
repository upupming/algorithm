#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int k, n;
string s, t;
int main() {
    cin >> k;
    while (k--) {
        cin >> n >> s >> t;
        vector<int> occ(26, 0);
        vector<pair<int, int>> swaps;
        for (int i = 0; i < n; i++) {
            occ[s[i] - 'a']++;
            occ[t[i] - 'a']++;
        }
        bool flag = true;
        for (int i = 0; i < 26; i++) {
            // cout << (char)(i + 'a') << ", " << occ[i] << endl;
            if (occ[i] % 2) {
                flag = false;
                break;
            }
        }
        for (int i = 0; i < n && flag; i++) {
            if (s[i] != t[i]) {
                // Case 1: s[i] == s[j], swap t[i] and s[j]
                size_t j = s.find(s[i], i + 1);
                if (j != string::npos) {
                    swap(s[j], t[i]);
                    swaps.push_back(make_pair(j, i));
                } else {
                // Case 2: s[i] == t[j], swap t[j] and s[j], and then swap s[j] and t[i]
                    j = t.find(s[i], i + 1);
                    assert(j != string::npos);
                    swap(t[j], s[j]);
                    swap(s[j], t[i]);
                    swaps.push_back(make_pair(j, j));
                    swaps.push_back(make_pair(j, i));
                }
            }
        }

        if (flag) {
            cout << "YES" << endl;
            int n = swaps.size();
            cout << n << endl;
            for (int i = 0; i < n; i++) {
                cout << (swaps[i].first + 1) << " " << (swaps[i].second + 1) << endl;
            }
        }
        else cout << "NO" << endl;
    }
    return 0;
}