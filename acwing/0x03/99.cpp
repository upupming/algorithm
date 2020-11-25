#include <iostream>
using namespace std;

int n, r, s[5050][5050];
void assign(int i, int j) {
    s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];
}
int getScore(int i, int j) {
    return s[i + r][j + r] - s[i + r][max(j, 0)] - s[max(i, 0)][j + r] + s[max(i, 0)][max(j, 0)];
}
int main() {
    cin >> n >> r;
    int x, y, w, maxX = 0, maxY = 0;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> w;
        // 可能有两个在同一个地方
        s[x + 1][y + 1] += w;
        maxX = max(x + 1, maxX), maxY = max(y + 1, maxY);
    }
    int maxScore = 0;
    // for (auto i : a) {
    //     for (auto j : i.second) {
    //         assign(i.first, j.first);
    //         if (i.first - r >= 1 && j.first - r >= 1) {
    //             int score = getScore(i.first - r, j.first - r);
    //             maxScore = max(maxScore, score);
    //         }
    //     }
    // }

    for (int i = 1; i <= maxX; i++) {
        for (int j = 1; j <= maxY; j++) {
            assign(i, j);
            int score = getScore(i - r, j - r);
            maxScore = max(maxScore, score);
        }
    }
    // for (int i = 1; i + r <= maxX; i++) {
    //     for (int j = 1; j + r <= maxY; j++) {
    //         int score = s[i + r][j + r] - s[i + r][j] - s[i][j + r] + s[i][j];
    //         maxScore = max(maxScore, score);
    //     }
    // }
    cout << maxScore << endl;
    return 0;
}