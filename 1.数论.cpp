#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // https://leetcode-cn.com/problems/reverse-integer/
    int reverse(int x)
    {
        int ret = 0;
        while (x != 0)
        {
            ret = ret * 10 + x % 10;
            x = x / 10;
        }
        return ret;
    }
};

// Test Case
int main()
{
    Solution *s = new Solution();
    printf("hello VSCode!\n");
    return 0;
}
