#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
class MovieRentingSystem {
   public:
    struct P {
        int shop, movie, price, idx;
        bool operator<(const P& b) const {
            if (price != b.price) return price < b.price;
            if (shop != b.shop) return shop < b.shop;
            return movie < b.movie;
        }
    };
    unordered_map<int, set<P>> unrentSet;
    unordered_map<int, unordered_map<int, P>> unrent;
    set<P> rentSet;
    unordered_map<int, unordered_map<int, P>> rentMap;
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (int i = 0; i < entries.size(); i++) {
            auto& e = entries[i];
            unrent[e[1]][e[0]] = {e[0], e[1], e[2], i};
            unrentSet[e[1]].insert({e[0], e[1], e[2], i});
        }
    }

    vector<int> search(int movie) {
        vector<int> ans;
        if (unrentSet.count(movie)) {
            auto it = unrentSet[movie].begin();
            int cnt = 0;
            while (cnt < 5 && it != unrentSet[movie].end()) {
                // 巧妙判是否删去
                if (!unrent[movie].count(it->shop)) {
                    it = unrentSet[movie].erase(it);
                } else {
                    ans.push_back(it->shop);
                    cnt++;
                    it++;
                }
            }
        }
        return ans;
    }

    void rent(int shop, int movie) {
        rentMap[movie][shop] = {shop, movie, unrent[movie][shop].price, unrent[movie][shop].idx};
        rentSet.insert({shop, movie, unrent[movie][shop].price, unrent[movie][shop].idx});

        unrent[movie].erase(shop);
    }

    void drop(int shop, int movie) {
        unrent[movie][shop] = {shop, movie, rentMap[movie][shop].price, rentMap[movie][shop].idx};
        unrentSet[movie].insert({shop, movie, rentMap[movie][shop].price, rentMap[movie][shop].idx});

        rentMap[movie].erase(shop);
    }

    vector<vector<int>> report() {
        vector<vector<int>> ans;
        int cnt = 0;
        auto it = rentSet.begin();
        while (cnt < 5 && it != rentSet.end()) {
            if (!rentMap[it->movie].count(it->shop)) {
                // 在循环中删除一个元素的方法有：
                // 1. rentSet.erase(it++);
                // C++ 11 新引入的 iterator erase (const_iterator position);
                // 2. it = rentSet.erase(it);
                // 但是这个方法是错误的
                /*
                rentSet.erase(it);
                // 这里 it 已经失效了，再++会出错
                it++;
                */
                rentSet.erase(it++);
            } else {
                ans.push_back({it->shop, it->movie});
                cnt++;
                it++;
            }
        }
        return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
/*
[null,null,[[1,7953]],null,null,[[11,9549]],[[11,9549]],[12],null,[],null,null,[[12,431],[17,6347]],null,[[12,431],[17,6347],[9,9630]],null,null,null,[[14,4321],[12,431],[17,6347],[12,6347]],null,null,null,[[11,7778],[14,4321],[12,431],[17,6347],[0,4988]],null]

[null,null,[[1,7953]],null,null,[[11,9549]],[[11,9549]],[12],null,[],null,null,[[12,431],[17,6347]],null,[[12,431],[17,6347],[9,9630]],null,null,null,[[14,4321],[12,431],[17,6347],[12,6347]],null,null,null,[[11,7778],[14,4321],[12,431],[17,6347],[0,4988]],null]
*/
