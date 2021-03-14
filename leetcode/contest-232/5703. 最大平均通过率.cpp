class Solution {
    struct P {
        int a, b;
        double g;
        double calc() const {
            return double(b - a) / b / (b + 1);
        }
        bool operator<(const P& x) const {
            return calc() < x.calc();
        }
    };

   public:
    double maxAverageRatio(vector<vector<int>>& cls, int e) {
        priority_queue<P> pq;
        for (auto& c : cls) {
            P p;
            p.a = c[0], p.b = c[1], p.g = (double)p.a / p.b;
            pq.push(p);
        }
        while (e--) {
            auto q = pq.top();
            pq.pop();
            q.a++, q.b++, q.g = (double)q.a / q.b;
            pq.push(q);
        }
        double ans = 0;
        while (pq.size()) {
            auto q = pq.top();
            pq.pop();
            ans += q.g;
        }
        return ans / cls.size();
    }
};
