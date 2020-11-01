// https://leetcode.com/contest/weekly-contest-213/problems/furthest-building-you-can-reach/

#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int diffsSum = 0;
        vector<int> diffs;
        for (int i = 1; i < heights.size(); i++) {
            int diff = heights[i] - heights[i - 1];
            diff = diff < 0 ? 0 : diff;
            diffsSum += diff;

            diffs.insert(
                upper_bound(
                    diffs.begin(),
                    diffs.end(),
                    diff),
                diff);

            if (diffsSum <= bricks) continue;

            // Check if is ok if using ladders
            // 我之前想的太复杂了（还尝试使用全部梯子去判断），这里只要减去之前最大的值，一定能够通过，因为上一次已经能通过，这次加了一个梯子删除了最大的 diff，这样还可能会留出多的 bricks 出来。然后后续不管如何，在这里使用梯子是合理的（因为不使用就不能够通过）
            if (ladders > 0) {
                diffsSum -= diffs[diffs.size() - 1];
                ladders--;
                continue;
            }

            return i - 1;
        }
        return heights.size() - 1;
    }
};