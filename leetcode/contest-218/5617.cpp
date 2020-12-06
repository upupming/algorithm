#include <string>
using namespace std;
class Solution {
   public:
    string interpret(string command) {
        string ans = "";
        for (int i = 0; i < command.length(); i++) {
            if (command[i] == 'G')
                ans += "G";
            else {
                if (command[i] == '(' && i + 1 < command.length() && command[i + 1] == 'a')
                    ans += "al", i += 3;
                else
                    ans += 'o', i += 1;
            }
        }
        return ans;
    }
};