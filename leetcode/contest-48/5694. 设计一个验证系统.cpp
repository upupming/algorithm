#include <bits/stdc++.h>
using namespace std;
class AuthenticationManager {
    unordered_map<string, int> mp;
    int t, last_size;

   public:
    AuthenticationManager(int _t) {
        t = _t;
    }

    void generate(string id, int ct) {
        mp[id] = ct + t;
    }

    void expire(int currentTime) {
        unordered_map<string, int> mp_new;
        for (auto &p : mp) {
            if (p.second <= currentTime) continue;
            mp_new[p.first] = p.second;
        }
        swap(mp_new, mp);
    }

    void renew(string tokenId, int currentTime) {
        expire(currentTime);
        for (auto &p : mp) {
            if (p.first == tokenId) {
                p.second = currentTime + t;
                return;
            }
        }
    }

    int countUnexpiredTokens(int currentTime) {
        expire(currentTime);
        return mp.size();
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
