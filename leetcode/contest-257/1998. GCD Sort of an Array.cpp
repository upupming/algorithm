#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
bool st[N];
int primes[N], cnt;
bool ok;

class Solution {
   public:
    vector<int> fa;
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        fa[fx] = fy;
    }
    bool gcdSort(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;
        if (!ok) {
            for (int i = 2; i < N; i++) {
                if (!st[i]) {
                    primes[cnt++] = i;
                }
                for (int j = 0; primes[j] < N / i; j++) {
                    st[primes[j] * i] = true;
                    if (i % primes[j] == 0) break;
                }
            }
            ok = true;
        }
        vector<int> idx;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < cnt; j++) {
                if (nums[i] % primes[j] == 0) {
                    mp[primes[j]].push_back(i);
                    // cout << primes[j] << " " << nums[i] << endl;
                }
                if (primes[j] > nums[i]) break;
            }
            fa.push_back(i);
            idx.push_back(i);
        }
        sort(idx.begin(), idx.end(), [&nums](int i, int j) {
            return nums[i] < nums[j];
        });
        for (auto& [p, arr] : mp) {
            for (int i = 0; i < arr.size() - 1; i++) {
                merge(arr[i], arr[i + 1]);
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (find(i) != find(idx[i])) return false;
        }
        return true;
    }
};
