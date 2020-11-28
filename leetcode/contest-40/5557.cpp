class Solution {
   public:
    int maxRepeating(string sequence, string word) {
        string s = "";
        int i = 0;
        while (true) {
            if (sequence.find(s) != string::npos) {
                s += word;
                i++;
            } else {
                break;
            }
        }
        return i - 1;
    }
};