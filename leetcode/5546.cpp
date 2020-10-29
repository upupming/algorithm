// https://leetcode.com/contest/weekly-contest-212/problems/slowest-key/
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        int maxTimes = 0;
        char maxCh = 0;
        for (int i = 0; i < releaseTimes.size(); i++) {
            int time;
            if (i == 0) {
                time = releaseTimes[i];
            } else {
                time = releaseTimes[i] - releaseTimes[i - 1];
            }
            if (time > maxTimes || (time == maxTimes && keysPressed[i] > maxCh)) {
                maxTimes = time;
                maxCh = keysPressed[i];
            }
        }

        return maxCh;
    }
};