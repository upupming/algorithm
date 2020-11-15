#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int t, s, ra, pa, rb, pb, c, r[100], p[100], visited[100][100];
int delta[][3][2] = {
    // (2, 2) 的邻居
    {{-1, -1},
     {0, -1},
     {0, 1}},
    // (3, 3) 的邻居
    {{1, 1},
     {0, -1},
     {0, 1}},
};

void findNext(int r, int p, vector<int>& nextR, vector<int>& nextP) {
    for (int i = 0; i < 3; i++) {
        int rn = r + delta[p % 2][i][0], pn = p + delta[p % 2][i][1];
        if (rn >= 1 && rn <= s && pn >= 1 && pn <= 2 * rn - 1 && !visited[rn][pn])
            nextR.push_back(rn), nextP.push_back(pn);
    }
}

// 返回得分
int dfs(int na, int nb, int rA, int pA, int rB, int pB, bool aTurn) {
    vector<int> nextRA, nextPA, nextRB, nextPB;
    findNext(rA, pA, nextRA, nextPA);
    findNext(rB, pB, nextRB, nextPB);
    if (nextRA.size() == 0 && nextPB.size() == 0) {
        // cout << "returning from: " << rA << ", " << pA << ", " << rB << ", " << pB << ", " << na << ", " << nb << endl;
        return na - nb;
    }

    int ans;
    if (aTurn) {
        if (nextRA.size() == 0) return dfs(
            na, nb, rA, pA, rB, pB, !aTurn);

        ans = INT_MIN;
        for (int i = 0; i < nextRA.size(); i++) {
            int rn = nextRA[i], pn = nextPA[i];
            assert(!visited[rn][pn]);
            visited[rn][pn] = 1;
            // A 尽量选得分大的方案
            ans = max(
                ans,
                dfs(
                    na + 1, nb, rn, pn, rB, pB, !aTurn));

            visited[rn][pn] = 0;
        }
    } else {
        if (nextRB.size() == 0) return dfs(
            na, nb, rA, pA, rB, pB, !aTurn);

        ans = INT_MAX;
        for (int i = 0; i < nextRB.size(); i++) {
            int rn = nextRB[i], pn = nextPB[i];
            assert(!visited[rn][pn]);
            visited[rn][pn] = 1;
            // B 尽量选得分小的方案
            ans = min(
                ans,
                dfs(
                    na, nb + 1, rA, pA, rn, pn, !aTurn));

            visited[rn][pn] = 0;
        }
    }

    return ans;
}

int solve() {
    visited[ra][pa] = visited[rb][pb] = 1;

    return dfs(1, 1, ra, pa, rb, pb, true);
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        fill_n(&visited[0][0], sizeof(visited) / sizeof(visited[0][0]), 0);
        cin >> s >> ra >> pa >> rb >> pb >> c;
        for (int i = 0; i < c; i++) {
            cin >> r[i] >> p[i];
            visited[r[i]][p[i]] = 1;
        }

        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}