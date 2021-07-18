#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int canBeTypedWords(string text, string brokenLetters) {
        int ans = 0;
        bool ok = true;
        for (int i = 0; i < text.size(); ++i) {
            if (text[i] == ' ') {
                if (ok) ans++;
                ok = true;
            }
            if (brokenLetters.find(text[i]) != string::npos) {
                ok = false;
            }
        }
        if (ok) ans++;
        return ans;
    }
};
