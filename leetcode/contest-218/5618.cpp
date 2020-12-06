#include <map>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxOperations(vector<int>& nums, int k) {
        int cnt = 0;
        map<int, int> mp;
        for (auto n : nums) mp[n]++;
        for (auto& m : mp) {
            while (m.second && mp[k - m.first] && (m.first != k - m.first || m.second >= 2)) {
                m.second--, mp[k - m.first]--, cnt++;
            }
        }
        return cnt;
    }
};