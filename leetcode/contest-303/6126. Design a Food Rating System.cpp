#include <bits/stdc++.h>
using namespace std;

struct P {
    string food;
    int rating;
    bool operator<(const P& b) const {
        if (rating != b.rating) return rating > b.rating;
        return food < b.food;
    }
};

class FoodRatings {
    map<string, string> food2Cos;
    map<string, int> food2Rating;
    map<string, multiset<P>> sets;

   public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
            sets[cuisines[i]].insert({foods[i], ratings[i]});
            food2Cos[foods[i]] = cuisines[i];
            food2Rating[foods[i]] = ratings[i];
        }
    }

    void changeRating(string food, int newRating) {
        auto& s = sets[food2Cos[food]];
        s.erase(s.find({food, food2Rating[food]}));
        s.insert({food, newRating});
        food2Rating[food] = newRating;
    }

    string highestRated(string cuisine) {
        return sets[cuisine].begin()->food;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
