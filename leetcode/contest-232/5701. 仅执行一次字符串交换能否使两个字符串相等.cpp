class Solution {
   public:
    bool areAlmostEqual(string s1, string s2) {
        if (s1 == s2) return true;
        int n = s1.length();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto t = s1;
                swap(t[i], t[j]);
                if (t == s2) return true;
            }
        }
        return false;
    }
};
