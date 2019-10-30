// 基本思想:每次取出 【占用座位数最少】的booking
#include <iostream>
#include <algorithm>

using namespace std;
#define inf 0x3fffffff

int t, n, q, from[30005], to[30005];
bool taken[1000005], booked[30005];

int solve() {
    int minSeats = inf;
    for (int i = 0; i < q; i++) {
        int seats = inf, bestJ = -1;
        for (int j = 0; j < q; j++) {
            int jSeats = 0;
            if (!booked[j]) {
                for (int k = from[j]; k <= to[j]; k++) {
                    if (!taken[k]) jSeats++;
                }
            } else continue;
            if (jSeats < seats) {
                seats = jSeats;
                bestJ = j;
            }
        }
        // cout << "bestJ = " << bestJ << ", seats = " << seats << endl;
        // 占用座位数最少的 j
        booked[bestJ] = true;
        for (int k = from[bestJ]; k <= to[bestJ]; k++) taken[k] = true;
        minSeats = min(minSeats, seats);
    }
    return minSeats;
}

int main() {
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        fill(taken, taken + n + 1, false);
        fill(booked, booked + q, false);
        scanf("%d%d", &n, &q);
        for (int i = 0; i < q; i++) scanf("%d%d", &from[i], &to[i]);
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}