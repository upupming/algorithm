#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

class MKAverage {
    int m, k;
    LL sum = 0;
    vector<int> v;
    multiset<int> nums, left, right;

   public:
    MKAverage(int _m, int _k) {
        m = _m, k = _k;
    }

    void addElement(int num) {
        v.push_back(num);
        if (v.size() < m) {
            nums.insert(num);
        } else if (v.size() == m) {
            nums.insert(num);
            for (int i = 0; i < k; i++) {
                left.insert(*nums.begin());
                nums.erase(nums.begin());
            }
            for (int i = 0; i < k; i++) {
                right.insert(*nums.rbegin());
                auto last = nums.end();
                last--;
                nums.erase(last);
            }
            for (auto& a : nums) {
                sum += a;
            }
        } else {
            int x = v[v.size() - 1 - m];

            auto last = left.end();
            last--;
            nums.insert(*last);
            sum += *last;
            left.erase(last);

            nums.insert(*right.begin());
            sum += *right.begin();
            right.erase(right.begin());

            if (x < *nums.begin())
                left.erase(left.lower_bound(x));
            else if (x > *nums.rbegin())
                right.erase(right.lower_bound(x));
            else {
                nums.erase(nums.lower_bound(x));
                sum -= x;
            }

            nums.insert(num), sum += num;
            while (left.size() < k) {
                left.insert(*nums.begin());
                sum -= *nums.begin();
                nums.erase(nums.begin());
            }
            while (right.size() < k) {
                auto last = nums.end();
                last--;
                right.insert(*last);
                sum -= *last;
                nums.erase(last);
            }

            assert(nums.size() == m - 2 * k);
            assert(left.size() == k);
            assert(right.size() == k);
        }
    }

    int calculateMKAverage() {
        if (v.size() < m) return -1;
        return round(sum / (m - 2 * k));
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
