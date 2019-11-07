#include <iostream>
#include <vector>

using namespace std;

int k, n;
string s, t;
int main() {
    cin >> k;
    while (k--) {
        cin >> n >> s >> t;
        int cnt = 0;
        vector<int> pos;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                cnt++;
                pos.push_back(i);
            }
        }
        bool flag = false;
        if (cnt == 0) flag = true;
        else if (cnt == 2) {
            flag = (s[pos[0]] == s[pos[1]] && t[pos[0]] == t[pos[1]]);
        }
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}