// https://www.youtube.com/watch?v=ZBHKZF5w4YU&ab_channel=TusharRoy-CodingMadeSimple

#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
   public:
    SegmentTree(const vector<int>& arr) {
        int n = arr.size();
        int m = 2 * pow(2, ceil(log2(n))) - 1;
        for (int i = 0; i < m; i++) {
            segTreeArr.push_back(INT_MAX);
        }
        this->arr = arr;
        constructSegmentTree(0, n - 1, 0);
    }
    int rangeQuery(int qLow, int qHigh) {
        return rangeQuery(qLow, qHigh, 0, arr.size() - 1, 0);
    }

   private:
    vector<int> segTreeArr;
    vector<int> arr;
    // pos is the root of the current segment tree
    void constructSegmentTree(int low, int high, int pos) {
        if (low == high) {
            segTreeArr[pos] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
        // Left subtree
        constructSegmentTree(low, mid, leftRootPos);
        // Right subtree
        constructSegmentTree(mid + 1, high, rightRootPos);

        segTreeArr[pos] = min(segTreeArr[leftRootPos], segTreeArr[rightRootPos]);
    }
    // pos is the root of the current segment tree
    int rangeQuery(int qLow, int qHigh, int low, int high, int pos) {
        // total overlap
        if (qLow <= low && qHigh >= high) return segTreeArr[pos];
        // no overlap
        if (qLow > high || qHigh < low) return INT_MAX;
        int mid = (low + high) / 2;
        int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
        return min(
            rangeQuery(qLow, qHigh, low, mid, leftRootPos),
            rangeQuery(qLow, qHigh, mid + 1, high, rightRootPos));
    }
};

int main() {
    // 0, 1, 2, 3, 4, 5, 6
    // 0, 3, 4, 2, 1, 6, -1
    vector<int> a{0, 3, 4, 2, 1, 6, -1};
    SegmentTree segTree(a);

    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            cout << "segTree.rangeQuery(" << i << ", " << j << ") is: " << segTree.rangeQuery(i, j) << endl;
        }
    }

    return 0;
}