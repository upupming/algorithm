// https://leetcode.com/contest/weekly-contest-213/problems/kth-smallest-instructions/

#include <bits/stdc++.h>
using namespace std;

// Input: destination = [2,3], k = 1
// Output: "HHHVV"
// Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
// ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].

void print(vector<string> a) {
    for (auto b : a) {
        cout << b << " ";
    }
    cout << endl;
}

long long nChoosek(long long n, long long k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    long long result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}
class Solution {
   public:
    string kthSmallestPath(vector<int>& destination, int k) {
        // r for vertical steps
        int r = destination[0], c = destination[1], n = r + c, nn = r + c;
        string ans = "";
        // 问题想复杂了，可以直接画一棵树，根据子树的排列组合数量和 k 的关系，每次只能是往左走或者往右走
        while (ans.length() != nn) {
            // if first step is horizontal
            long long tmp = nChoosek(--n, r);
            if (k > tmp) {
                ans += "V";
                k -= tmp;
                r--;
            } else {
                ans += "H";
            }
        }
        return ans;
    }
};