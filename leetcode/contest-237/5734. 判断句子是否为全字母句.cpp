#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    bool checkIfPangram(string sentence) {
        unordered_set<char> s;
        for (auto& ch : sentence) {
            s.insert(ch);
        }
        return s.size() == 26;
    }
};
