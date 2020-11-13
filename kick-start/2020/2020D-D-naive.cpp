#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

// #define DEBUG

// TODO: Test 2 现在还过不了
// 参考：https://codeforces.com/blog/entry/80040#comment-662229

int t, n, q, d[100010], s, k, startIdx, endIdx, curIdx;
unordered_map<int, int> mpCur, mpStart, mpEnd, ansArr;
vector<int> sArr, kArr;

int solve() {
    curIdx = startIdx = endIdx = s;
    for (int i = 0; i < k - 1; i++) {
        if (startIdx - 1 > 0 && endIdx + 1 <= n) {
            // 2 choices
            int leftDifficulty = d[startIdx - 2], rightDifficulty = d[endIdx - 1];
            if (leftDifficulty < rightDifficulty) {
                curIdx = --startIdx;
            } else {
                curIdx = ++endIdx;
            }
        } else if (startIdx - 1 <= 0) {
            curIdx = ++endIdx;
        } else {
            curIdx = --startIdx;
        }
    }

    return curIdx;
}

template <typename T>
std::vector<size_t> argsort(const std::vector<T> &array) {
    std::vector<size_t> indices(array.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&array](int left, int right) -> bool {
                  // sort indices according to corresponding array element
                  return array[left] < array[right];
              });

    return indices;
}

int solve1(int s, int k) {
    // 如果之前已经计算过，直接返回
    if (mpCur[k]) return mpCur[k];
    // 看看之前算到了哪里
    int cacheK = k - 1;
    while (cacheK > 0 && !mpCur[cacheK]) cacheK--;
    // 之前根本没有算过
    if (cacheK == 0) {
        mpCur[1] = mpStart[1] = mpEnd[1] = s;
        cacheK++;
    }

    for (int i = cacheK; i < k; i++) {
        if (mpStart[i] - 1 > 0 && mpEnd[i] + 1 <= n) {
            // 2 choices
            int leftDifficulty = d[mpStart[i] - 2], rightDifficulty = d[mpEnd[i] - 1];
            if (leftDifficulty < rightDifficulty) {
                mpCur[i + 1] = mpStart[i + 1] = mpStart[i] - 1;
                mpEnd[i + 1] = mpEnd[i];
            } else {
                mpCur[i + 1] = mpEnd[i + 1] = mpEnd[i] + 1;
                mpStart[i + 1] = mpStart[i];
            }
        } else if (mpStart[i] - 1 <= 0) {
            mpCur[i + 1] = mpEnd[i + 1] = mpEnd[i] + 1;
            mpStart[i + 1] = mpStart[i];
        } else {
            mpCur[i + 1] = mpStart[i + 1] = mpStart[i] - 1;
            mpEnd[i + 1] = mpEnd[i];
        }
    }

    return mpCur[k];
}

int main() {
#ifdef DEBUG
    ifstream cin("input.in");
#endif

    cin >> t;
    for (int i = 1; i <= t; i++) {
        mpCur.clear(), mpStart.clear(), mpEnd.clear();
        sArr.clear(), kArr.clear(), ansArr.clear();
        printf("Case #%d: ", i);

        cin >> n >> q;

        for (int i = 0; i < n - 1; i++) cin >> d[i];
        for (int i = 0; i < q; i++) {
            cin >> s >> k;
            sArr.push_back(s), kArr.push_back(k);

            // if (i > 0) printf(" ");
            // printf("%d", solve());
        }
        vector<size_t> sorted = argsort(sArr);
        for (int i = 0; i < q; i++) {
            if (i > 0 && sArr[sorted[i]] != sArr[sorted[i - 1]]) mpCur.clear(), mpStart.clear(), mpEnd.clear();
            ansArr[sorted[i]] = solve1(sArr[sorted[i]], kArr[sorted[i]]);
        }
        for (int i = 0; i < q; i++) {
            if (i > 0) printf(" ");
            printf("%d", ansArr[i]);
        }

        printf("\n");
    }
    return 0;
}