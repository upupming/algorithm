/*
sum_e, sum_r 表示所有玩具的 e 和 r 的和

如果最终停在第 i 玩具的话，一定是第 2 轮，因为第 1 轮不可能停下（之前都没玩过），假设是在第 3 轮停下的话，那距离上次玩经过的时间一定是 sum_e - e[i]，也就是说 sum_e - e[i] < r[i]，满足这个条件的话，第 2 轮也一定会停下来的；同理，更不可能是在第 4, 5, ... 轮

判断能不能无限玩下去和计算删除最少使得玩的时间最长这两个问题需要用两趟来完成：

1. 能不能无限玩下去

满足 sum_e - e[i] < r[i] 的玩具是一定会停下来的，因此我们优先删除不等号两边差异较大的玩具（因为一定会被删除，删除过程中 sum_e 也是在减小的），这就是贪心的思想，移一下项得到 sum_e < e[i] + r[i]，把玩具按照 e+r 从大到小排序，逐渐删除直到：
1. 所有玩具都会停下来，删到只剩下最后一个玩具了，那么说明不可能无限玩下去
2. 删到 >= 2 个玩具的时候，发现没有 sum_e < e[i] + r[i] 的玩具了，说明可以无限玩下去

2. 不能无限玩下去的话，计算最长玩的时间

优先删除编号最小的不能满足玩具，因为这是唯一的可能增加玩的时长的方法，删除编号第 2 小的还是会卡在第 1 个停止

删除之后前面可能产生新的不能玩的玩具，在产生的新的不能玩的玩具里面需要先删除 e[i] + r[i] 较大的类似上面的过程,因此要用优先队列维护，first 存一下标号

N * Ei = 10^14，爆 int，需要用 long long
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
typedef pair<int, int> PII;

int t, n;
struct P {
    LL e, r, idx;
    bool operator<(const P& q) const {
        return e + r > q.e + q.r;
    }
} p[N];
bool cmp(P a, P b) {
    return a.idx < b.idx;
}
LL sum_e;

void solve() {
    // 1. 判断能否无限玩下去
    sort(p, p + n);
    for (int i = 0; i < n; i++) {
        // 删除当前最不满足的玩具
        if (sum_e < p[i].e + p[i].r) {
            sum_e -= p[i].e;
        } else {
            cout << i << " INDEFINITELY" << endl;
            return;
        }
    }
    // 2. 判断最长能玩多长的时间
    // 还原初始顺序
    sort(p, p + n, cmp);
    // 再求一遍 sum
    sum_e = 0;
    for (int i = 0; i < n; i++) sum_e += p[i].e;
    // 至少能够玩 1 轮，cur_cnt 表示当前删除数量，cur_ans 表示当前可玩时间
    LL ans = sum_e, cnt = 0, cur_ans = sum_e, cur_cnt = 0;
    priority_queue<PII> pq;
    // 按照编号从小到大遍历
    for (int i = 0; i < n; i++) {
        // 如果不能满足就删除
        if (sum_e < p[i].e + p[i].r) {
            cur_cnt++;
            sum_e -= p[i].e;
            // 只需要减去第一趟的时间，因为第二趟都没加上
            cur_ans -= p[i].e;
            // 看看前面有哪些会因为不满足而删掉
            while (pq.size() && sum_e < pq.top().first) {
                cur_cnt++;
                auto now = pq.top();
                pq.pop();
                sum_e -= p[now.second].e;
                // 玩的时间里面，第一趟和第二趟都要减去，第二趟在之前的循环里加上过
                cur_ans -= 2 * p[now.second].e;
            }
        } else {
            // 虽然现在满足，但是之后后面删掉之后可能不满足，先放进最大堆里
            pq.push({p[i].e + p[i].r, i});
            cur_ans += p[i].e;
            if (cur_ans > ans) {
                ans = cur_ans;
                cnt = cur_cnt;
            }
        }
    }
    cout << cnt << " " << ans << endl;
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        sum_e = 0;
        for (int i = 0; i < n; i++) {
            cin >> p[i].e >> p[i].r;
            p[i].idx = i;
            sum_e += p[i].e;
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
