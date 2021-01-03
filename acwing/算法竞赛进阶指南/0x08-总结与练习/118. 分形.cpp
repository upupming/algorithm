/*
分形一般用递归函数写比较方便
数据的表示方式比较重要，可以用 r 行 c 列的 vector 来表示指定输入对应的结果

看完 y 总解答发现其实可以只运行一次 getBoxes，n - 1 就是 n 的左上角部分
*/
#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> getBoxes(int n) {
    if (n == 1) return {vector<char>(1, 'X')};
    auto s = getBoxes(n - 1);
    int r = s.size(), c = s[0].size();
    vector<vector<char>> ans(3 * r, vector<char>(3 * c, ' '));
    int pos[5][2] = {
        {0, 0},
        {0, 2 * c},
        {r, c},
        {2 * r, 0},
        {2 * r, 2 * c},
    };
    for (int i = 0; i < 5; i++) {
        for (int a = 0; a < r; a++) {
            for (int b = 0; b < c; b++) {
                ans[a + pos[i][0]][b + pos[i][1]] = s[a][b];
            }
        }
    }
    return ans;
}
int n;
int main() {
    while ((cin >> n) && n != -1) {
        vector<vector<char>> s = getBoxes(n);
        int r = s.size(), c = s[0].size();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << s[i][j];
            }
            cout << endl;
        }

        cout << "-" << endl;
    }
    return 0;
}