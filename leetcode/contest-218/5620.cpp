#include <string>
using namespace std;

class Solution {
   public:
    int numBits(int n) {
        int ans = 0;
        while (n) ans++, n >>= 1;
        return ans;
    }
    int myPow(int x) {
        int ans = 1, a = 2;
        while (x > 0) {
            if (x & 1) ans = ((long long)ans * a) % 1000000007;
            a = ((long long)a * a) % 1000000007;
            x >>= 1;
        }
        return ans;
    }
    int concatenatedBinary(int n) {
        int ans = 0;
        for (int i = n, bits = 0; i >= 1; i--) {
            // cout << i << " " << bits << endl;
            ans = ((long long)ans + i * (long long)myPow(bits)) % 1000000007;
            bits += numBits(i);
        }
        return ans;
    }
};