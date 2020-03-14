#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, m, k;
int idToIndex[10005], indexToId[310];
bool isBoy[310];
set<int> w[310];

bool cmp(const vector<int>& a, const vector<int>& b) {
    return (a[0] == b[0]) ? (a[1] < b[1])
                          : (a[0] < b[0]);
}

int main() {
    cin >> n >> m;
    int a, b;
    int curIndex = 1;
    for (int i = 0; i < m; i++) {
        string aa, bb;
        cin >> aa >> bb;
        // 这里考虑如何处理 0000 和 -0000 的情况
        int a = stoi(aa), b = stoi(bb);
        if (aa == "0000") {
            a = 10000;
        } else if (aa == "-0000") {
            a = -10000;
        }
        if (bb == "0000") {
            b = 10000;
        } else if (bb == "-0000") {
            b = -10000;
        }
        if (idToIndex[abs(a)] == 0) {
            idToIndex[abs(a)] = curIndex;
            indexToId[curIndex] = abs(a);
            isBoy[curIndex] = (a > 0);
            curIndex++;
        }
        if (idToIndex[abs(b)] == 0) {
            idToIndex[abs(b)] = curIndex;
            indexToId[curIndex] = abs(b);
            isBoy[curIndex] = (b > 0);
            curIndex++;
        }
        int indexA = idToIndex[abs(a)], indexB = idToIndex[abs(b)];
        w[indexA].insert(indexB);
        w[indexB].insert(indexA);
    }
    cin >> k;
    for (int i = 0; i < k; i++) {
        vector<vector<int>> res;
        cin >> a >> b;
        int indexA = idToIndex[abs(a)], indexB = idToIndex[abs(b)];
        // cout << "a = " << a << ", b = " << b << endl;
        // cout << "indexA = " << indexA << ", indexB = " << indexB << endl;
        // 如果这个 id 之前没有出现过
        if (indexA == 0 || indexB == 0) {
            cout << 0 << endl;
            continue;
        }

        // 遍历 a 的所有邻居和 b 的所有邻居
        // set 只保证了 index 的从小到大，未保证 id 的从小到大
        for (set<int>::iterator it = w[indexA].begin(); it != w[indexA].end(); it++) {
            // 必须是同性别的，本身相连的不能算！！！
            bool shouldSkip = ((a > 0) && !isBoy[*it]) || ((a < 0) && isBoy[*it]) || indexToId[*it] == abs(b);
            if (shouldSkip) continue;
            for (set<int>::iterator it1 = w[indexB].begin(); it1 != w[indexB].end(); it1++) {
                // 必须是同性别的
                bool shouldSkip = ((b > 0) && !isBoy[*it1]) || ((b < 0) && isBoy[*it1]) || indexToId[*it1] == abs(a);
                if (shouldSkip) continue;
                if (w[*it].count(*it1)) {
                    res.push_back(vector<int>({indexToId[*it], indexToId[*it1]}));
                }
            }
        }

        sort(res.begin(), res.end(), cmp);

        cout << res.size() << endl;

        for (vector<vector<int>>::iterator it = res.begin(); it != res.end(); it++) {
            // 注意打印格式
            printf("%04d %04d\n", (*it)[0] % 10000, (*it)[1] % 10000);
        }
    }
    return 0;
}

/**
边界情况：自己跟自己相连
4 4
1 2
2 4
4 3
3 1
1
1 2

边界情况，异性别情况：
4 4
1 2
2 -4
-4 -3
-3 1
1
1 2

边界情况，三角形
3 3
1 2
2 3
1 3
1
1 3

边界情况，完全图
4 6
1 2
1 3
1 4
2 3
2 4
3 4
1
1 3
*/