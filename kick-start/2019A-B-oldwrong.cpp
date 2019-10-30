// 此题失误：理论推导不严格，后来才发现不是选最高点

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define inf 0x3fffffff

int t, r, c, mh[260][260], mh1[260][260], maxMh;
string str;
// 初始就为 1 的点，曼哈顿距离均为 0
vector<pair<int, int>> sources;
pair<int, int> maxPos;

void dfs(int rr, int cc, int depth, int mh[][260] = mh) {
    if (rr < 0 || rr >= r || cc < 0 || cc >= c) return;
    // 剪枝
    if (mh[rr][cc] <= depth) return;
    mh[rr][cc] = depth;
    dfs(rr, cc + 1, depth + 1, mh);
    dfs(rr, cc - 1, depth + 1, mh);
    dfs(rr + 1, cc, depth + 1, mh);
    dfs(rr - 1, cc, depth + 1, mh);
}

void findMaxPos(int mh[][260] = mh) {
    maxMh = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (mh[i][j] > maxMh) {
                maxMh = mh[i][j];
                maxPos = make_pair(i, j);
            }
        }
    }
}

void print(int mh[][260] = mh) {
    maxMh = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << " " << mh[i][j];
        }
        cout << endl;
    }
}
void copyMh() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mh1[i][j] = mh[i][j];
        }
    }
}

int solve() {
    for (auto it = sources.begin(); it != sources.end(); it++) {
        dfs(it->first, it->second, 0);
    }
    findMaxPos();
    // 原矩阵全都是 1，无需修改
    if (maxMh == 0) return 0;
    // cout << "maxMh = " << maxMh << endl;
    // cout << maxPos.first << ", " << maxPos.second << endl;
    int minMaxMh = maxMh;
    // 修改曼哈顿距离最大的点
    copyMh(); dfs(maxPos.first, maxPos.second, 0, mh1);
    findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    // 修改边上四个点
    copyMh(); dfs(maxPos.first - 1, maxPos.second, 0, mh1);
    findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    copyMh(); dfs(maxPos.first + 1, maxPos.second, 0, mh1);
    findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    copyMh(); dfs(maxPos.first, maxPos.second - 1, 0, mh1);
    findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    copyMh(); dfs(maxPos.first, maxPos.second + 1, 0, mh1);
    findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    
    // // 暴力枚举所有点
    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         copyMh();
    //         dfs(i, j, 0, mh1);
    //         findMaxPos(mh1); minMaxMh = min(minMaxMh, maxMh);
    //         // cout << i << ", " << j << ", " << maxMh << endl;
    //         // cout << "pos = " << maxPos.first << ", " << maxPos.second << endl;
    //     }
    // }
    return minMaxMh;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> r >> c;
        sources.clear();
        fill(mh[0], mh[0] + 260 * 260, inf);
        for (int i = 0; i < r; i++) {
            cin >> str;
            for (int j = 0; j < c; j++) {
                if (str[j] == '1') {
                    sources.push_back(make_pair(i, j));
                }
            }
        }
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}

/**
3
3 3
111
111
111
1 2
11
5 5
10001
00000
00000
00000
10001

*/