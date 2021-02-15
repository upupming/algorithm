/*
对拍驱动程序
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
const int N = 1e4;
// const

int main() {
    system("g++ ./random.cpp -o random.out");
    system("g++ -std=c++11 ./kick-start/2020/RoundC/D.\\ Candies-BF.cpp -o bf.out");
    system("g++ -std=c++11 ./kick-start/2020/RoundC/D.\\ Candies.cpp -o algo.out");
    for (int T = 1; T <= N; T++) {
        // 生成随机数据
        system("./random.out > data.in");
        // 记录运行的 CPU 时间
        double st = clock();
        // 暴力解法输出正确答案
        system("./bf.out < data.in > data.ans");
        double ed = clock();
        // 优化解法输出待检查答案
        system("./algo.out < data.in > data.out");

        if (system("diff data.out data.ans")) {
            puts("Wrong Answer");
            return 0;
        } else {
            printf("Accepted, 测试点 #%d, 用时 %.01f\n", T, ed - st);
        }
    }
    return 0;
}