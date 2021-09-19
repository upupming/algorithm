#include <bits/stdc++.h>
using namespace std;
class DetectSquares {
    vector<vector<int>> all;
    unordered_map<int, unordered_map<int, int>> cnt;

   public:
    DetectSquares() {
    }

    void add(vector<int> point) {
        cout << "add " << point[0] << " " << point[1] << endl;
        ;
        all.push_back(point);
        cnt[point[0]][point[1]]++;
    }

    int count(vector<int> point) {
        int ans = 0;
        for (auto &p : all) {
            if (p[0] == point[0] || p[1] == point[1]) continue;
            if (abs(point[0] - p[0]) != abs(point[1] - p[1])) continue;
            if (cnt.count(p[0]) && cnt[p[0]].count(point[1]) && cnt.count(point[0]) && cnt[point[0]].count(p[1])) {
                ans += cnt[p[0]][point[1]] * cnt[point[0]][p[1]];
            }
        }
        return ans;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
