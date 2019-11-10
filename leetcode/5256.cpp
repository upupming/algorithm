class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        int n = colsum.size(), sum = 0, sum0 = 0, sum1 = 0;
        vector<int> r0(n), r1(n);
        
        for (int i = 0; i < n; i++) {
            sum += colsum[i];
            if (colsum[i] == 2) {
                r0[i] = r1[i] = 1;
                sum0 += 1;
                sum1 += 1;
            } else if (colsum[i] == 2) {
                // r0[i] = r1[i] = 0; not necesssary
            }
        }
        if (sum != upper + lower || sum0 > upper || sum1 > lower) return vector<vector<int>>(0, vector<int>(0));
        for (int i = 0; i < n; i++) {
            if (colsum[i] == 1) {
                if (sum0 != upper) {
                    r0[i] = 1;
                    sum0 += 1;
                } else {
                    r1[i] += 1;
                }
            }
        }
        vector<vector<int>> v;
        v.push_back(r0);v.push_back(r1);
        return v;
    }
};