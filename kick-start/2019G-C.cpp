#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int t, n, h, a[50], b[50];

struct Pair {
    // pa, pb for happiness of A(Aninda), B(Boon-Nam)
    long long pa, pb;
    Pair(const Pair & p) {
        this->pa = p.pa;
        this->pb = p.pb;
    }
    Pair() { this->pa = this->pb = 0;}
} pointPair;

int cmp(Pair a, Pair b) {
    if (a.pa != b.pa) return a.pa < b.pa;
    else return a.pb < b.pb;
}

// O(3^N)
void dfs(int shiftNo, int total, const Pair& tmpPair, vector<Pair>& pairs) {
    if (shiftNo == total) {
        pairs.push_back(tmpPair);
        return;
    }
    Pair p1(tmpPair), p2(tmpPair), p3(tmpPair);
    // A guards
    p1.pa += a[shiftNo];
    dfs(shiftNo+1, total, p1, pairs);
    // B guards
    p2.pb += b[shiftNo];
    dfs(shiftNo+1, total, p2, pairs);
    // A & B guard
    p3.pa += a[shiftNo];
    p3.pb += b[shiftNo];
    dfs(shiftNo+1, total, p3, pairs);
}

long long solve() {
    long long res = 0;

    vector<Pair> pairsA, pairsB;
    pointPair.pa = pointPair.pb = 0;
    // divide into 2 sets
    dfs(0, n / 2, pointPair, pairsA);
    dfs(n / 2, n, pointPair, pairsB);

    sort(pairsA.begin(), pairsA.end(), cmp);
    sort(pairsB.begin(), pairsB.end(), cmp);

    // for all pairs: O(3^{N/2})
    for (vector<Pair>::iterator it = pairsA.begin(); it != pairsA.end(); it++) {
        long long i = -1, low = 0, high = pairsB.size() - 1;
        // binary search: log(3^{N/2})
        while(low <= high) {
            long long mid = (low + high) / 2;
            if (pairsB[mid].pa < h - it->pa) {
                low = mid + 1;
            } else {
                i = mid;
                high = mid - 1;
            }
        }
        for (; i < pairsB.size() && i >= 0; i++) {
            if (pairsB[i].pb >= (h - it->pb)) res++;
        }
    }
    return res;
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d%d", &n, &h);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
