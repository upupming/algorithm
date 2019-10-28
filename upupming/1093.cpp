#include <iostream>

using namespace std;

// 动态规划，进一步优化可以去除数组
int p[100005], pa[100005], pat[100005];

int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'P') {
            pa[i + 1] = pa[i]; pat[i + 1] = pat[i];
            p[i + 1] = (p[i] + 1) % 1000000007;
        }
        else if (s[i] == 'A') {
            p[i + 1] = p[i]; pat[i + 1] = pat[i];
            pa[i + 1] = (pa[i] + p[i]) % 1000000007;
        }
        else if (s[i] == 'T') {
            p[i + 1] = p[i]; pa[i + 1] = pa[i];
            // cout << i << ", " << pat[i] << ", " << pa[i] << endl;
            pat[i + 1] = (pat[i] + pa[i]) % 1000000007;
        }
    }
    // for (int i = 0; i <= s.length(); i++) {
    //     cout << i << ", " << s[i] << ": " << p[i] << ", " << pa[i] << ", " << pat[i] << endl;
    // }
    cout << pat[s.length()] << endl;
    return 0;
}