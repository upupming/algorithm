class SmallestInfiniteSet {
    set<int> s;

   public:
    SmallestInfiniteSet() {
        for (int i = 1; i <= 1e3; i++) s.insert(i);
    }

    int popSmallest() {
        int x = *s.begin();
        s.erase(s.begin());
        return x;
    }

    void addBack(int num) {
        s.insert(num);
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
