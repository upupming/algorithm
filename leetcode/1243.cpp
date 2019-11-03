class Solution {
public:
    vector<int> transformArray(vector<int>& a) {
        while (true) {
            bool changed = false;
            vector<int> b;
            b.push_back(a[0]);
            for (int i = 1; i < a.size() - 1; i++) {
                if (a[i] > a[i-1] && a[i] > a[i+1]) {
                    b.push_back(a[i]-1);
                    changed = true;
                }
                else if (a[i] < a[i-1] && a[i] < a[i+1]) {
                    b.push_back(a[i]+1);
                    changed = true;
                } else b.push_back(a[i]);
            }
            b.push_back(a[a.size() - 1]);
            if (!changed) break;
            else a = b;
        }
        return a;
    }
};