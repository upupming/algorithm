#include <bits/stdc++.h>
using namespace std;

class CountIntervals {
    typedef pair<int, int> pii;
    int ans = 0;
    set<pii> st;

   public:
    CountIntervals() {
    }

    void add(int left, int right) {
        // st 中已有的区间总是保持互不相交的
        auto it = st.lower_bound({left - 1, -1});
        while (it != st.end()) {
            // 不可能合并了
            if (it->second >= right + 1) break;
            right = max(right, it->first);
            left = min(left, it->second);
            ans -= it->first - it->second + 1;
            st.erase(it++);
        }
        ans += right - left + 1;
        st.insert({right, left});
    }

    int count() {
        return ans;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
