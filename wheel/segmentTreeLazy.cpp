// https://www.youtube.com/watch?v=xuoQdt5pHj0&t=299s&ab_channel=TusharRoy-CodingMadeSimple

#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class SegmentTree {
   public:
    SegmentTree(const vector<T>& arr) {
        // 4 -> 4 + 3 = 7
        // 5 -> 8 + 7 = 15, aka: 5 -> 8 -> 2 * 8 - 1
        int m = 2 * pow(2, ceil(log2(arr.size()))) - 1;
        for (int i = 0; i < m; i++) {
            // TODO: change here if not for minimum calculation
            segTreeArr.push_back(std::numeric_limits<T>::max());
            lazyTreeArr.push_back(0);
        }
        this->arr = (&arr);
        constructSegmentTree(0, arr.size() - 1, 0);
    }
    void updateRangeLazy(int qLow, int qHigh, T delta) {
        updateRangeLazy(qLow, qHigh, delta, 0, (*arr).size() - 1, 0);
    }
    T rangeQueryLazy(int qLow, int qHigh) {
        return rangeQueryLazy(qLow, qHigh, 0, (*arr).size() - 1, 0);
    }

   private:
    vector<T> segTreeArr, lazyTreeArr;
    // don't copy the original array, but using pointer to save memory
    const vector<T>* arr;
    // pos is the root of the current segment tree
    void constructSegmentTree(int low, int high, int pos) {
        if (low == high) {
            segTreeArr[pos] = (*arr)[low];
            return;
        }

        int mid = (low + high) / 2;
        int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
        // Left subtree
        constructSegmentTree(low, mid, leftRootPos);
        // Right subtree
        constructSegmentTree(mid + 1, high, rightRootPos);

        // TODO: change here if not for minimum calculation
        segTreeArr[pos] = min(segTreeArr[leftRootPos], segTreeArr[rightRootPos]);
    }
    // important: make sure all propagations is done at `pos`
    void pushPropagation(int low, int high, int pos) {
        if (lazyTreeArr[pos] != 0) {
            int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
            segTreeArr[pos] += lazyTreeArr[pos];
            // if not a leaf node, push down the cache to children
            if (low != high) {
                lazyTreeArr[leftRootPos] += lazyTreeArr[pos];
                lazyTreeArr[rightRootPos] += lazyTreeArr[pos];
            }
            lazyTreeArr[pos] = 0;
        }
    }
    void updateRangeLazy(int qLow, int qHigh, T delta, int low, int high, int pos) {
        pushPropagation(low, high, pos);
        int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
        // total overlap
        if (qLow <= low && qHigh >= high) {
            segTreeArr[pos] += delta;
            // if not a leaf node, record the value to lazy-tree
            if (low != high) {
                lazyTreeArr[leftRootPos] += delta;
                lazyTreeArr[rightRootPos] += delta;
            }
            return;
        }
        // no overlap
        if (qLow > high || qHigh < low) return;
        // otherwise partial overlap, look both left and right
        int mid = (low + high) / 2;
        updateRangeLazy(qLow, qHigh, delta, low, mid, leftRootPos);
        updateRangeLazy(qLow, qHigh, delta, mid + 1, high, rightRootPos);
        // TODO: change here if not for minimum calculation
        segTreeArr[pos] = min(
            segTreeArr[leftRootPos],
            segTreeArr[rightRootPos]);
    }
    T rangeQueryLazy(int qLow, int qHigh, int low, int high, int pos) {
        pushPropagation(low, high, pos);

        // total overlap
        if (qLow <= low && qHigh >= high) return segTreeArr[pos];
        // no overlap
        // TODO: change here if not for minimum calculation
        if (qLow > high || qHigh < low) return std::numeric_limits<T>::max();
        // otherwise partial overlap, look both left and right
        int mid = (low + high) / 2;
        int leftRootPos = 2 * pos + 1, rightRootPos = 2 * pos + 2;
        return min(
            rangeQueryLazy(qLow, qHigh, low, mid, leftRootPos),
            rangeQueryLazy(qLow, qHigh, mid + 1, high, rightRootPos));
    }
};

int main() {
    // 0, 1, 2, 3, 4, 5, 6
    // 0, 3, 4, 2, 1, 6, -1
    vector<int> a{0, 3, 4, 2, 1, 6, -1};
    SegmentTree<int> segTree(a);

    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            cout << "segTree.rangeQueryLazy(" << i << ", " << j << ") is: " << segTree.rangeQueryLazy(i, j) << endl;
        }
    }

    // 0,    1,    2,   3,   4,   5,  6
    // 100, 103, 104, 102, 101, 106, 99
    segTree.updateRangeLazy(0, 6, 100);
    cout << endl
         << endl;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            cout << "segTree.rangeQueryLazy(" << i << ", " << j << ") is: " << segTree.rangeQueryLazy(i, j) << endl;
        }
    }

    // 0,       1,    2,    3,   4,   5,  6
    // 1100, 1103, 1104, 1102, 101, 106, 99
    segTree.updateRangeLazy(0, 3, 1000);
    cout << endl
         << endl;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            cout << "segTree.rangeQueryLazy(" << i << ", " << j << ") is: " << segTree.rangeQueryLazy(i, j) << endl;
        }
    }

    return 0;
}