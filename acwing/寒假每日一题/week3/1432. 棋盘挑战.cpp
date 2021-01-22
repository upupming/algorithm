/*
枚举每一行放置的位置即可
*/
#include <iostream>
#include <vector>
using namespace std;
const int N = 15;

int n, d[2 * N], dr[2 * N], col[N], cnt;
vector<int> ans;
// 返回搜到的方案数
// row 表示正在搜的行
int dfs(int row) {
    if (row >= n) {
        if (cnt < 3) {
            for (int i = 0; i < n; i++) cout << ans[i] << " ";
            cout << endl;
            cnt++;
        }
        return 1;
    }
    int res = 0;
    // 枚举每一种可能的位置
    for (int j = 0; j < n; j++) {
        int x = row + j, y = row - j + n;
        // 如果同一列、或者同一对角线已经被占用过
        if (col[j] || d[x] || dr[y]) continue;
        col[j] = d[x] = dr[y] = 1;
        ans.push_back(j + 1);

        res += dfs(row + 1);

        ans.pop_back();
        col[j] = d[x] = dr[y] = 0;
    }
    return res;
}
int main() {
    cin >> n;
    cout << dfs(0) << endl;
    return 0;
}