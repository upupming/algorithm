typedef pair<long long, int> PII;
class Solution {
   public:
    int mostBooked(int n, vector<vector<int>> &meetings) {
        sort(meetings.begin(), meetings.end(), [](auto &m1, auto &m2) {
            return m1[0] < m2[0];
        });
        vector<int> cnt(n, 0);
        // <结束时间, room id>
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        set<int> free;
        for (int i = 0; i < n; i++) free.insert(i);
        for (auto meet : meetings) {
            long long s = meet[0], e = meet[1];
            while (pq.size() && pq.top().first <= s) {
                free.insert(pq.top().second);
                pq.pop();
            }
            // delay to the first time of pq top
            if (!free.size()) {
                auto t = pq.top().first;
                // 这里不能把所有 t 时刻结束的都放入 free
                // https://leetcode.cn/problems/meeting-rooms-iii/solution/shuang-dui-mo-ni-pythonjavacgo-by-endles-ctwc/1738683
                free.insert(pq.top().second);
                pq.pop();
                e = e - s + t, s = t;
            }
            auto it = free.begin();
            pq.push({e, *it});
            cnt[*it]++;
            free.erase(it);
        }
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (cnt[i] > cnt[ans]) ans = i;
        }
        return ans;
    }
};
