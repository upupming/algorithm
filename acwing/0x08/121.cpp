/*
二分 + 离散化

二分畜栏边长，从 1 到 10000，计算能够容纳的三叶草数
关键是给定边长为 mid 的畜栏，如何计算能够容纳的最多的四叶草数
用 O(n^2) 时间预处理求出二维前缀和，可以 O(1) 时间计算出任意矩形区域的前缀和
之后枚举所有坐标作为畜栏的左下角点
因为坐标范围是 10^4 但是最多 500 个点，还需要离散化，将枚举左下角点的时间复杂度降低到 O(500^2)
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int c, n, sum[1010][1010];
pair<int, int> p[510];
vector<int> numbers;
int query(int x) {
    return lower_bound(numbers.begin(), numbers.end(), x) - numbers.begin();
}
// side 为边长，计算能否包含 c 个三叶草
bool valid(int side) {
    for (int x1 = 0, x2 = 1; x2 < numbers.size(); x2++) {
        // 找到第一个 x1+1 满足边长正好是 side
        while (numbers[x2] - numbers[x1 + 1] > side - 1) x1++;
        for (int y1 = 0, y2 = 1; y2 < numbers.size(); y2++) {
            while (numbers[y2] - numbers[y1 + 1] > side - 1) y1++;
            if (sum[x2][y2] - sum[x2][y1] - sum[x1][y2] + sum[x1][y1] >= c) return true;
        }
    }
    return false;
}
int main() {
    cin >> c >> n;
    // 前缀和数组会用到下标0，所以需要把0也离散化一下。
    // 如果不离散化 0，那么 sum 的下标不能从 1 开始，计算 sum[0][0] 就很麻烦
    numbers.push_back(0);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        numbers.push_back(p[i].first);
        numbers.push_back(p[i].second);
    }
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    sort(numbers.begin(), numbers.end());

    for (int i = 0; i < n; i++) {
        int x = query(p[i].first), y = query(p[i].second);
        sum[x][y] += 1;
    }
    // 前缀和
    for (int i = 1; i <= numbers.size(); i++) {
        for (int j = 1; j <= numbers.size(); j++) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    int l = 1, r = 10010;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (!valid(mid))
            l = mid + 1;
        else
            r = mid;
    }

    cout << l << endl;
    return 0;
}