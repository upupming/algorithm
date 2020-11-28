// Forward declaration of compare API.
// bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution {
   public:
    vector<int> specialSort(int N) {
        vector<int> a;
        for (int i = 1; i <= N; i++) {
            int l = 0, r = a.size();
            int cnt = 0;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (compare(i, a[mid]))
                    r = mid;
                else
                    l = mid + 1;
            }
            a.insert(a.begin() + l, i);
        }
        return a;
    }
};