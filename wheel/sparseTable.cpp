// https://www.geeksforgeeks.org/sparse-table/
// RMQ (Range Minumum Query) 算法之一
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void buildSparseTable(int *a, int n) {
}

class SparseTable {
   public:
    SparseTable(vector<int> &a) {
        this->a = &a;
        int m = ceil(log2(a.size()));
        table = vector<vector<int>>(a.size(), vector<int>(m));
        // 初始化：st[i][0] = a[i]
        for (int i = 0; i < a.size(); i++) table[i][0] = a[i];

        for (int j = 1; j < m; j++) {
            // 递推公式：st[i][j] = min(st[i][j-1], st[i + 2^{j-1}][j-1])
            for (int i = 1; i <= a.size() - (1 << j); i++) {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    // [2, 10]
    int query(int qLow, int qHigh) {
        // j = 3
        int j = floor(log2(qHigh - qLow + 1));
        return min(
            // table[2][3], 2 - 9
            table[qLow][j],
            // table[3][3], 3 - 10
            table[qHigh - pow(2, j) + 1][j]);
    }

   private:
    vector<int> *a;
    vector<vector<int>> table;
};

int main() {
    // //            0, 1, 2, 3, 4,  5, 6,  7,  8
    // vector<int> a{7, 2, 3, 0, 5, 10, 3, 12, 18};
    // 0, 1, 2, 3, 4, 5, 6
    // 0, 3, 4, 2, 1, 6, -1
    vector<int> a{0, 3, 4, 2, 1, 6, -1};

    SparseTable st(a);

    // cout << st.query(0, 4) << endl;
    // cout << st.query(4, 7) << endl;
    // cout << st.query(7, 8) << endl;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            cout << "st.query(" << i << ", " << j << ") is: " << st.query(i, j) << endl;
        }
    }
    return 0;
}