/*
树的最小表示：只要两个树是同构的，最小表示就是一样的
儿子节点的最小表示按照字典序排列，然后拼接即可
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int t;
string a, b;
// 返回遍历序列 s 的最小表示
string dfs(string& s, int& u) {
    vector<string> seqs;
    // 当前的出边
    u++;
    // 所有子树
    while (s[u] == '0') seqs.push_back(dfs(s, u));
    // 当前的回边
    u++;

    sort(seqs.begin(), seqs.end());
    string res = "0";
    for (auto s : seqs) res += s;
    res += '1';
    // cout << u << " " << res << endl;
    return res;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> a >> b;
        a = '0' + a + '1';
        b = '0' + b + '1';
        int ua = 0, ub = 0;
        if (dfs(a, ua) == dfs(b, ub))
            puts("same");
        else
            puts("different");
    }
    return 0;
}
