#include <bits/stdc++.h>
using namespace std;
/*
1. 用 next_permutation 算第 k 个数 target
2. 从 num 变成 target 需要的最小交换次数可以用贪心来求，没遇到一个不同的位置 i，就从 target 后面找到 j 满足 target[j] == num[i]，将 target[j] 一步一步移到前面来，需要的步数是 j-i
时间复杂度: O(n^2)
第 2 步实际上就是求逆序对，不过我们的目标不是 12345 这样的有序串，而是任意的串，这种情况也可以转化为标准的逆序对来处理
直接用 O(n^2) 的算法比较简单，可以用归并排序优化成 O(n log n)
*/
class Solution {
   public:
    int getMinSwaps(string num, int k) {
        string target = num;
        while (k--) next_permutation(target.begin(), target.end());

        int ans = 0, n = num.size();
        for (int i = 0; i < n; i++) {
            if (num[i] != target[i]) {
                for (int j = i + 1; j < n; j++) {
                    if (target[j] == num[i]) {
                        for (int k = j; k > i; k--) {
                            swap(target[k], target[k - 1]);
                        }
                        ans += j - i;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
