class Solution {
   public:
    int findCenter(vector<vector<int>>& edges) {
        unordered_map<int, int> deg;
        int maxDeg = 0, ans;
        for (auto& e : edges) {
            int x = e[0], y = e[1];
            deg[x]++, deg[y]++;
            if (deg[x] > maxDeg) {
                maxDeg = deg[x];
                ans = x;
            }
            if (deg[y] > maxDeg) {
                maxDeg = deg[y];
                ans = y;
            }
        }
        return ans;
    }
};
