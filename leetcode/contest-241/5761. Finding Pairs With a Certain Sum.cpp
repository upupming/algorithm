#include <bits/stdc++.h>
using namespace std;
class FindSumPairs {
   public:
    vector<int> nums1, nums2;
    unordered_map<int, int> cnt2;
    FindSumPairs(vector<int>& _nums1, vector<int>& _nums2) {
        nums1 = _nums1, nums2 = _nums2;
        for (auto& a : nums2) {
            cnt2[a]++;
        }
    }

    void add(int index, int val) {
        int old = nums2[index];
        nums2[index] += val;
        cnt2[old]--, cnt2[nums2[index]]++;
    }

    int count(int tot) {
        int ans = 0;
        for (auto& a : nums1) {
            int val = tot - a;
            if (cnt2.count(val)) ans += cnt2[val];
        }
        return ans;
    }
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
