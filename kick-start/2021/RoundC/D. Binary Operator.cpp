#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
const int N = 110;

int t, n, idx[N];
string e[N];
vector<int> val[N];
bool same[N][N];
unordered_map<string, unordered_map<string, vector<int>>> h;

int random(int n) {
    return (long long)rand() * rand() % n;
}

string toString(const vector<int> &A) {
    string ans;
    for (auto x : A) ans += to_string(x);
    return ans;
}
bool cmp(const vector<int> &A, const vector<int> &B) {
    if (A.size() != B.size()) {
        return A.size() < B.size();
    }
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] < B[i];
    }
    return false;
}
void out(const vector<int> &A) {
    for (int i = A.size() - 1; i >= 0; i--) {
        cout << A[i];
    }
}
vector<int> add(const vector<int> &A, const vector<int> &B) {
    if (A.size() < B.size()) return add(B, A);
    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i++) {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t) C.push_back(t);
    return C;
}
vector<int> mul(const vector<int> &A, const vector<int> &B) {
    vector<int> C(A.size() + B.size());
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }
    int t = 0;
    for (int i = 0; i < C.size(); i++) {
        t += C[i];
        C[i] = t % 10;
        t /= 10;
    }
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
vector<int> calc_hash(const vector<int> &A, const vector<int> &B) {
    vector<int> ans;
    auto a = toString(A), b = toString(B);
    if (h.count(a) && h[a].count(b)) return h[a][b];
    int c = random(INT_MAX);
    while (c > 0) {
        ans.push_back(c % 10);
        c /= 10;
    }
    return h[a][b] = ans;
}

vector<int> calc_exp(int i) {
    vector<int> ans;
    vector<vector<int>> nums;
    vector<char> ops;
    string s = e[i];
    int n = s.length();
    vector<int> val;
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            val.push_back(s[i] - '0');
            if (i + 1 < n && s[i + 1] >= '0' && s[i + 1] <= '9') continue;
            reverse(val.begin(), val.end());
            nums.push_back(val);
            val.resize(0);
        } else if (s[i] == '(') {
            ops.push_back('(');
        } else if (s[i] == ')') {
            while (ops.size() && ops.back() != '(') {
                // 出栈一个符号就计算一下
                char op = ops.back();
                ops.pop_back();
                // 计算逻辑
                {
                    auto y = nums.back();
                    nums.pop_back();
                    auto x = nums.back();
                    nums.pop_back();
                    vector<int> z;
                    switch (op) {
                        case '+':
                            z = add(x, y);
                            break;
                        case '*':
                            z = mul(x, y);
                            break;
                        case '#':
                            z = calc_hash(x, y);
                            break;
                    }
                    // cout << x << op << y << " = " << z << endl;
                    // 把运算结果放回栈中
                    nums.push_back(z);
                }
            }
            // 左括号出栈（如果有的话）
            if (ops.size()) ops.pop_back();
        } else {
            // 运算符，直接入栈，这题简化了，括号内最多只有一个运算符
            ops.push_back(s[i]);
        }
    }
    return nums.front();
}

void solve() {
    // 开始认为两两之间都相等，需要经受 10 次考验，受不住的就设置为不相等
    memset(same, 1, sizeof same);
    // 随机生成 10 次 total function 进行消除
    for (int k = 0; k < 10; k++) {
        h.clear();
        for (int i = 1; i <= n; i++) {
            val[i] = calc_exp(i);
            // cout << i << " ";
            // out(val[i]);
            // cout << endl;
            for (int j = 1; j < i; j++) {
                // val[i] != val[j]
                if (cmp(val[i], val[j]) || cmp(val[j], val[i])) {
                    same[i][j] = same[j][i] = false;
                }
            }
        }
    }
    int p = 1;
    for (int i = 1; i <= n; i++) {
        bool found = false;
        for (int j = 1; j < i; j++) {
            if (same[j][i]) {
                found = true, idx[i] = idx[j];
            }
        }
        if (!found) {
            idx[i] = p++;
        }
        cout << idx[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> e[i];
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
