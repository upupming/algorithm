#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int n;
int r = 5, c = 5, delta[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
vector<int> v;
bool check(int i, int j) { return (i >= 0 && i < r && j >= 0 && j < c); }

void relax(vector<int>& u, int i, int j) {
    for (int l = 0; l < 4; l++) {
        int r_nei = i + delta[l][0], c_nei = j + delta[l][1];
        if (check(r_nei, c_nei)) u[r_nei * c + c_nei] ^= 1;
    }
}

int solve() {
    int ans = INT_MAX;
    // 固定第一行的方案，使用位运算枚举
    for (int i = 0; i < (1 << r); i++) {
        auto u = v;
        int cnt = 0;
        for (int j = 0; j < c; j++) {
            // 选择第一行的第 j 列进行点击
            if ((i >> j) & 1) {
                u[j] ^= 1, cnt++;
                relax(u, 0, j);
            }
        }
        // 一旦第一行固定，第二行也固定，以此类推，全部的行都被固定
        for (int j = 1; j < r; j++) {
            for (int k = 0; k < c; k++) {
                if (!u[(j - 1) * c + k]) {
                    u[j * c + k] ^= 1, cnt++;
                    relax(u, j, k);
                }
            }
        }
        // 看一下最后一行是否全为 1
        bool ok = true;
        for (int k = 0; k < c; k++) {
            if (!u[(r - 1) * c + k]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            // cout << i << ", " << cnt << endl;
            ans = min(ans, cnt);
        }
    }
    return (ans == INT_MAX || ans > 6) ? -1 : ans;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        v.clear();
        string s;
        for (int i = 0; i < r; i++) {
            cin >> s;
            for (int j = 0; j < c; j++) {
                v.push_back(s[j] - '0');
            }
        }

        cout << solve() << endl;
    }
    return 0;
}