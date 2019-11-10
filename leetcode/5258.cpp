class Solution {
    int ss(int i, vector<vector<int>> s, vector<string>& words) {
        if (i == words.size()) return 0;
        // cout << i << ", " << words.size() << endl;
        vector<vector<int>> sb = s;
        string word = words[i];
        int maxScore = 0;
        bool flag = true;
        for (int i = 0; i < word.length(); i++) {
            // word is not able to construct
            if (s[word[i]].size() == 0) {
                flag = false;
                maxScore = 0;
                break;
            }
            maxScore += s[word[i]][0];
            s[word[i]].erase(s[word[i]].begin());
        }
        int tmp = ss(i + 1, sb, words);
        cout << (i + 1) << ", " << tmp << endl;
        return max(maxScore + ss(i + 1, s, words), tmp);
    }
    
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int n = letters.size();
        vector<vector<int>> s(300, vector<int>());
        for (int i = 0; i < n; i++) {
            s[letters[i]].push_back(score[letters[i] - 'a']);
        }
        // for (char i = 'a'; i <= 'z'; i++) {
        //     sort(s[i].begin(), s[i].end(), greater<int>());
        //     for (int j = 0; j < s[i].size(); j++) {
        //         cout << s[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        
        return ss(0, s, words);
    }
};