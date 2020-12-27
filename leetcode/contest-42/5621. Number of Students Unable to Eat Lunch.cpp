#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int countStudents(vector<int>& stu, vector<int>& sand) {
        int ans = 0;
        vector<int> visited(stu.size(), false);
        for (int i = 0; i < sand.size(); i++) {
            bool ok = false;
            for (int j = 0; j < stu.size(); j++) {
                if (!visited[j] && stu[j] == sand[i]) {
                    visited[j] = true;
                    ans++;
                    ok = true;
                    break;
                }
            }
            if (!ok) break;
        }

        return stu.size() - ans;
    }
};