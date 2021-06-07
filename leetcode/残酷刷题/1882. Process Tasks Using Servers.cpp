#include <bits/stdc++.h>
using namespace std;
/*
空闲服务器队列，按照 weight, idx 排序，每次分配给一个任务之后，进入繁忙服务器队列
繁忙服务器队列，按照结束时间排序，结束之后进入空闲服务器队列，因为最后多出一些任务的时候需要等待繁忙服务器，所以结束时间相同也需要按照 weight 排序
*/
typedef array<int, 2> AI2;
typedef array<int, 3> AI3;
class Solution {
   public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<int> ans(tasks.size());
        priority_queue<AI2, vector<AI2>, greater<>> free;
        priority_queue<AI3, vector<AI3>, greater<>> busy;
        // 将所有服务器放入空闲队列
        for (int i = 0; i < servers.size(); i++) {
            // wight, idx
            free.push({servers[i], i});
        }
        queue<int> jobs;
        // 处理所有的 tasks 放入任务队列中
        for (int j = 0; j < tasks.size(); j++) {
            // 看看哪些服务器变成空闲了
            while (busy.size() && busy.top()[0] <= j) {
                auto b = busy.top();
                busy.pop();
                free.push({b[1], b[2]});
            }
            // 放入 jobs 队列
            jobs.push(j);
            // 如果有空闲服务器可以使用的话，一个一个执行 jobs 的任务
            while (free.size() && jobs.size()) {
                auto job = jobs.front();
                jobs.pop();
                auto f = free.top();
                free.pop();
                // endTime, idx
                busy.push({j + tasks[job], f[0], f[1]});
                ans[job] = f[1];
            }
        }
        // 可能有在 n-1 时间内仍未执行完的任务
        // 这个时候 free 队列一定为空，否则 jobs 会在之前已经执行了
        // 直接看 busy 队列即可，每次拿一个出来，直接跳到 server 的空闲时间
        while (jobs.size()) {
            assert(free.empty());
            auto j = jobs.front();
            jobs.pop();
            auto b = busy.top();
            busy.pop();
            busy.push({b[0] + tasks[j], b[1], b[2]});
            ans[j] = b[2];
        }
        return ans;
    }
};
