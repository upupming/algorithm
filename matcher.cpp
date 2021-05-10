/*
对拍驱动程序
*/
#include <cstdlib>
#include <ctime>
#include <iostream>
const int N = 1e4;
const std::string bf = "kick-start/2021/RoundB/B.\\ naive.cpp";
const std::string algo = "kick-start/2021/RoundB/B.\\ Longest\\ Progression.cpp";
const std::string randomGenerator = "kick-start/2021/RoundB/B.\\ random.cpp";

/*
封装一下 `system`，支持 ctrl + c 退出整个对拍程序
https://stackoverflow.com/a/3771792/8242705
*/
int mySystem(const char* command) {
    int result = system(command);
    if (WIFEXITED(result)) {
        // printf("Exited normally with status %d\n", WEXITSTATUS(result));
    } else if (WIFSIGNALED(result)) {
        printf("Exited with signal %d\n", WTERMSIG(result));
        exit(1);
    } else {
        printf("Not sure how we exited.\n");
    }
    return result;
}

int main() {
    mySystem(("g++ -std=c++11 -o random.out " + randomGenerator).c_str());
    mySystem(
        ("g++ -std=c++11 -o bf.out " + bf).c_str());
    mySystem(
        ("g++ -std=c++11 -o algo.out " + algo).c_str());
    for (int T = 1; T <= N; T++) {
        // 生成随机数据
        mySystem("./random.out > data.in");
        // 记录运行的 CPU 时间
        double st = clock();
        // 暴力解法输出正确答案
        mySystem("./bf.out < data.in > data.ans");
        double ed = clock();
        // 优化解法输出待检查答案
        mySystem("./algo.out < data.in > data.out");

        if (mySystem("diff data.out data.ans")) {
            puts("\033[1;31mWrong Answer\033[0m");
            return -1;
        } else {
            printf("\033[1;32mAccepted\033[0m, 测试点 #%d, 用时 %.01f\n", T, ed - st);
        }
    }
    return 0;
}
