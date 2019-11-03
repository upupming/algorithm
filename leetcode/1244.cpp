class Leaderboard {
    vector<vector<int>> board;
    static int cmp(vector<int> p1, vector<int> p2) {
        return p1[1] > p2[1];
    }
public:
    Leaderboard() {
        
    }
    
    void addScore(int playerId, int score) {
        bool found = false;
        int j;
        for (int i = 0; i < board.size(); i++) {
            if (board[i][0] == playerId) {
                j = i;
                found = true;
                break;
            }
        }
        if (found)
            board[j][1] += score;
        else {
            vector<int> p;
            p.push_back(playerId);
            p.push_back(score);
            board.push_back(p);
        }
    }
    
    int top(int K) {
        sort(board.begin(), board.end(), cmp);
        int sum = 0;
        for (int i = 0; i < K && i < board.size(); i++) {
            sum += board[i][1];
        }
        return sum;
    }
    
    void reset(int playerId) {
        for (int i = 0; i < board.size(); i++) {
            if (board[i][0] == playerId) {
                board[i][1] = 0;
                return;
            }
        }
    }
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */