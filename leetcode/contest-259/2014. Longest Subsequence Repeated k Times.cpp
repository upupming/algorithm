class Solution {
    int k;
    unordered_map<char, int> cnt;
    string s, t, ans;

    void dfs() {
        unordered_map<char, int> cnt2(cnt);
        for (auto [ch, freq] : cnt2) {
            // 排列方式 t 给定了，判断是否出现了 k 次
            t.push_back(ch);
            if (t.size() > ans.size() || (t.size() == ans.size() && t > ans)) {
                int times = 0, pos = 0;
                for (char c : s)
                    if (c == t[pos]) {
                        pos++;
                        // 一次匹配完毕，times+=1,pos归零重新开始匹配
                        if (pos == t.size())
                            times++, pos = 0;
                    }

                if (times >= k)
                    ans = t;
            }
            // 出现次数减去 k
            cnt[ch] -= k;
            if (cnt[ch] < k)
                cnt.erase(ch);
            dfs();
            t.pop_back();
            cnt[ch] = freq;
        }
    }

   public:
    string longestSubsequenceRepeatedK(string s, int k) {
        this->k = k;
        int n = s.size();
        for (char c : s)
            cnt[c]++;
        string to_del;
        for (auto [ch, freq] : cnt)
            if (freq < k)
                to_del.push_back(ch);
        // 只留下出现次数 >= k 的那些字符，字符种数最多只有 7
        for (char ch : to_del)
            cnt.erase(ch);

        for (char c : s)
            if (cnt.count(c))
                this->s.push_back(c);

        dfs();

        return ans;
    }
};
