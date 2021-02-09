/*
计算每个月 13 号到 1900 年 1 月 1 日（星期一）经过的天数即可
经过的天数为 x（包含 1900.1.1），那么就是「星期 (x % 7) + 1」
需要计算一下闰年
*/
#include <iostream>
using namespace std;
const int s = 1900;

int n, ans[7];
int days[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int isLeap(int y) {
    if (y % 4 == 0 && y % 100 != 0) return 1;
    if (y % 400 == 0) return 1;
    return 0;
}
int idx[7] = {6, 0, 1, 2, 3, 4, 5};
int main() {
    cin >> n;
    for (int i = s, passed = 0; i < s + n; i++) {
        auto d = days[isLeap(i)];
        for (int j = 0; j < 12; j++) {
            int x = passed + 13;
            ans[x % 7]++;
            passed += d[j];
        }
    }
    for (int i = 0; i < 7; i++) {
        cout << ans[idx[i]] << " ";
    }
    cout << endl;
    return 0;
}