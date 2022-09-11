class Solution {
   public:
    int minGroups(vector<vector<int>>& ivs) {
        sort(ivs.begin(), ivs.end(), [](auto& a, auto& b) {
            return a[0] < b[0];
        });
        multiset<int> h;
        for (auto& iv : ivs) {
            int s = iv[0], e = iv[1];
            auto it = (h.lower_bound(s));
            if (!h.size() || it == h.begin()) {
                h.insert(e);
            } else {
                h.erase(--it);
                h.insert(e);
            }
        }
        return h.size();
    }
};
